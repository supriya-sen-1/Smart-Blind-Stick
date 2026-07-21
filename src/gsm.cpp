/*****************************************************************
 * File    : gsm.cpp
 * Project : Smart Blind Stick
 * Board   : ESP32 DevKit V1
 *
 * Description:
 * SIM800L GSM Driver
 *****************************************************************/

#include "gsm.h"

/**************************************************************
 * Constructor
 **************************************************************/
GSM::GSM(HardwareSerial &serial)
{
    gsmSerial = &serial;
    networkConnected = false;

    statusState = StatusState::IDLE;
    statusStepStart = 0;
    statusRxBuffer = "";

    resultModuleReady = false;
    resultNetworkAvailable = false;
    resultSignalStrength = -1;
}

/**************************************************************
 * Initialize GSM Module
 * (One-shot, runs at boot before the main loop starts - blocking
 * here is fine.)
 **************************************************************/
void GSM::begin()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("Initializing SIM800L...");
    Serial.println("========================================");

    delay(1000);

    if (isModuleReady())
    {
        Serial.println("SIM800L Module Detected");
    }
    else
    {
        Serial.println("SIM800L Not Responding");
    }

    if (isNetworkAvailable())
    {
        Serial.println("Network Registered");
    }
    else
    {
        Serial.println("Network Not Available");
    }

    Serial.print("Signal Strength : ");
    Serial.println(getSignalStrength());

    Serial.println("========================================");
}

/**************************************************************
 * update()
 * Call every loop(). Drains any unsolicited URCs from the
 * module AND advances the async status-check state machine
 * (if one is running). Never blocks.
 **************************************************************/
void GSM::update()
{
    // Only free-drain to the debug console when the status
    // state machine isn't mid-conversation with the module -
    // otherwise we'd steal the bytes it's waiting on.
    if (statusState == StatusState::IDLE || statusState == StatusState::DONE)
    {
        while (gsmSerial->available())
        {
            Serial.write(gsmSerial->read());
        }
    }

    statusStateMachineStep();
}

/**************************************************************
 * beginStatusCheck()
 * Kicks off a non-blocking module/network/signal check.
 * Results land in resultModuleReady / resultNetworkAvailable /
 * resultSignalStrength and get printed once DONE is reached.
 **************************************************************/
void GSM::beginStatusCheck()
{
    if (statusState != StatusState::IDLE && statusState != StatusState::DONE)
    {
        // Already running - ignore, let the current one finish.
        return;
    }

    while (gsmSerial->available())
    {
        gsmSerial->read();
    }

    statusRxBuffer = "";
    statusState = StatusState::MODULE_SEND;
}

bool GSM::isStatusCheckBusy()
{
    return statusState != StatusState::IDLE && statusState != StatusState::DONE;
}

bool GSM::lastModuleReady()      { return resultModuleReady; }
bool GSM::lastNetworkAvailable() { return resultNetworkAvailable; }
int  GSM::lastSignalStrength()   { return resultSignalStrength; }

/**************************************************************
 * statusStateMachineStep()
 * One non-blocking step of the async status check. Reads
 * whatever bytes are available right now, checks for the
 * expected token, checks for step timeout, and either stays
 * in place, advances, or moves to the next command. Nothing
 * in here ever waits.
 **************************************************************/
void GSM::statusStateMachineStep()
{
    switch (statusState)
    {
        case StatusState::IDLE:
        case StatusState::DONE:
            return;

        case StatusState::MODULE_SEND:
            gsmSerial->println("AT");
            statusRxBuffer = "";
            statusStepStart = millis();
            statusState = StatusState::MODULE_WAIT;
            return;

        case StatusState::MODULE_WAIT:
        {
            while (gsmSerial->available())
            {
                statusRxBuffer += (char)gsmSerial->read();

                if (statusRxBuffer.indexOf("OK") != -1)
                {
                    resultModuleReady = true;
                    statusState = StatusState::NETWORK_SEND;
                    return;
                }
            }

            if (millis() - statusStepStart >= 2000)
            {
                resultModuleReady = false;
                statusState = StatusState::NETWORK_SEND;
            }
            return;
        }

        case StatusState::NETWORK_SEND:
            while (gsmSerial->available())
            {
                gsmSerial->read();
            }
            gsmSerial->println("AT+CREG?");
            statusRxBuffer = "";
            statusStepStart = millis();
            statusState = StatusState::NETWORK_WAIT;
            return;

        case StatusState::NETWORK_WAIT:
        {
            while (gsmSerial->available())
            {
                statusRxBuffer += (char)gsmSerial->read();

                if (statusRxBuffer.indexOf("+CREG: 0,1") != -1 ||
                    statusRxBuffer.indexOf("+CREG: 0,5") != -1)
                {
                    resultNetworkAvailable = true;
                    networkConnected = true;
                    statusState = StatusState::SIGNAL_SEND;
                    return;
                }
            }

            if (millis() - statusStepStart >= 3000)
            {
                resultNetworkAvailable = false;
                networkConnected = false;
                statusState = StatusState::SIGNAL_SEND;
            }
            return;
        }

        case StatusState::SIGNAL_SEND:
            while (gsmSerial->available())
            {
                gsmSerial->read();
            }
            gsmSerial->println("AT+CSQ");
            statusRxBuffer = "";
            statusStepStart = millis();
            statusState = StatusState::SIGNAL_WAIT;
            return;

        case StatusState::SIGNAL_WAIT:
        {
            while (gsmSerial->available())
            {
                statusRxBuffer += (char)gsmSerial->read();
            }

            int index = statusRxBuffer.indexOf("+CSQ:");

            // Early exit the moment we have the full "+CSQ: N,M" line -
            // don't wait out the rest of the timeout once we have it.
            if (index != -1)
            {
                int commaIndex = statusRxBuffer.indexOf(',', index);

                if (commaIndex != -1)
                {
                    String rssi = statusRxBuffer.substring(index + 6, commaIndex);
                    resultSignalStrength = rssi.toInt();
                    statusState = StatusState::DONE;
                    printStatusReport();
                    return;
                }
            }

            if (millis() - statusStepStart >= 3000)
            {
                resultSignalStrength = -1;
                statusState = StatusState::DONE;
                printStatusReport();
            }
            return;
        }
    }
}

void GSM::printStatusReport()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("            GSM STATUS");
    Serial.println("========================================");
    Serial.print("Module   : ");
    Serial.println(resultModuleReady ? "OK" : "FAIL");
    Serial.print("Network  : ");
    Serial.println(resultNetworkAvailable ? "Connected" : "Not Connected");
    Serial.print("RSSI     : ");
    Serial.println(resultSignalStrength);
    Serial.println("========================================");
}

/**************************************************************
 * Send AT Command (blocking helper - only for one-shot,
 * user-triggered calls: begin(), sendSMS(), makeCall(), sendSOS())
 **************************************************************/
bool GSM::sendATCommand(const String &command,
                        const String &expectedResponse,
                        uint32_t timeout)
{
    while (gsmSerial->available())
    {
        gsmSerial->read();
    }

    gsmSerial->println(command);

    String response = "";

    unsigned long startTime = millis();

    while (millis() - startTime < timeout)
    {
        while (gsmSerial->available())
        {
            char c = gsmSerial->read();
            response += c;

            if (response.indexOf(expectedResponse) != -1)
            {
                return true;
            }
        }
    }

    Serial.println();
    Serial.print("AT Command Failed : ");
    Serial.println(command);

    return false;
}

/**************************************************************
 * Check Module (blocking - see header for when this is safe)
 **************************************************************/
bool GSM::isModuleReady()
{
    return sendATCommand("AT", "OK", 2000);
}

/**************************************************************
 * Check Network Registration (blocking)
 **************************************************************/
bool GSM::isNetworkAvailable()
{
    if (sendATCommand("AT+CREG?", "+CREG: 0,1", 3000))
    {
        networkConnected = true;
        return true;
    }

    if (sendATCommand("AT+CREG?", "+CREG: 0,5", 3000))
    {
        networkConnected = true;
        return true;
    }

    networkConnected = false;

    return false;
}

/**************************************************************
 * Get Signal Strength (blocking, with early exit)
 **************************************************************/
int GSM::getSignalStrength()
{
    while (gsmSerial->available())
    {
        gsmSerial->read();
    }

    gsmSerial->println("AT+CSQ");

    String response = "";

    unsigned long startTime = millis();

    while (millis() - startTime < 3000)
    {
        while (gsmSerial->available())
        {
            response += (char)gsmSerial->read();
        }

        int index = response.indexOf("+CSQ:");

        if (index != -1)
        {
            int commaIndex = response.indexOf(',', index);

            if (commaIndex != -1)
            {
                String rssi = response.substring(index + 6, commaIndex);
                return rssi.toInt();
            }
        }
    }

    return -1;
}

/**************************************************************
 * Print GSM Module Information (blocking one-shot version -
 * kept for setup()/manual use. For periodic status in loop(),
 * use beginStatusCheck() instead.)
 **************************************************************/
void GSM::printModuleInfo()
{
    resultModuleReady = isModuleReady();
    resultNetworkAvailable = isNetworkAvailable();
    resultSignalStrength = getSignalStrength();
    printStatusReport();
}

/**************************************************************
 * Send SMS
 **************************************************************/
bool GSM::sendSMS(const String &phoneNumber,
                  const String &message)
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("Sending SMS...");
    Serial.println("========================================");

    if (!sendATCommand("AT+CMGF=1", "OK", 3000))
    {
        Serial.println("Failed to Enable SMS Text Mode");
        return false;
    }

    while (gsmSerial->available())
    {
        gsmSerial->read();
    }

    gsmSerial->print("AT+CMGS=\"");
    gsmSerial->print(phoneNumber);
    gsmSerial->println("\"");

    String response = "";
    unsigned long startTime = millis();
    bool gotPrompt = false;

    while (millis() - startTime < 5000)
    {
        while (gsmSerial->available())
        {
            char c = gsmSerial->read();
            response += c;

            if (response.indexOf(">") != -1)
            {
                gotPrompt = true;
                break;
            }
        }

        if (gotPrompt)
        {
            break;
        }
    }

    if (!gotPrompt)
    {
        Serial.println("SMS Prompt Not Received");
        return false;
    }

    gsmSerial->print(message);
    gsmSerial->write(26); // CTRL+Z

    response = "";
    startTime = millis();

    while (millis() - startTime < 15000)
    {
        while (gsmSerial->available())
        {
            char c = gsmSerial->read();
            response += c;

            if (response.indexOf("+CMGS:") != -1)
            {
                Serial.println("SMS Sent Successfully");
                return true;
            }

            if (response.indexOf("ERROR") != -1)
            {
                Serial.println("SMS Sending Failed");
                return false;
            }
        }
    }

    Serial.println("SMS Timeout");

    return false;
}

/**************************************************************
 * Make Voice Call
 **************************************************************/
bool GSM::makeCall(const String &phoneNumber)
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("Calling Emergency Contact...");
    Serial.println("========================================");

    if (!isModuleReady())
    {
        Serial.println("SIM800L Not Ready");
        return false;
    }

    if (!isNetworkAvailable())
    {
        Serial.println("Network Not Available");
        return false;
    }

    gsmSerial->print("ATD");
    gsmSerial->print(phoneNumber);
    gsmSerial->println(";");

    delay(1000);

    Serial.print("Calling : ");
    Serial.println(phoneNumber);

    return true;
}

/**************************************************************
 * Hang Up Call
 **************************************************************/
void GSM::hangUp()
{
    gsmSerial->println("ATH");

    delay(1000);

    Serial.println("Call Ended");
}

/**************************************************************
 * Send Emergency SMS
 **************************************************************/
bool GSM::sendEmergencySMS(const String &phoneNumber,
                           const String &gpsLink)
{
    String message;

    message += "******** EMERGENCY ALERT ********\n\n";
    message += "Smart Blind Stick User\n";
    message += "Needs Immediate Assistance.\n\n";
    message += "Current Location:\n";
    message += gpsLink;
    message += "\n\nPlease Reach Immediately.";

    return sendSMS(phoneNumber, message);
}

/**************************************************************
 * SOS Procedure
 * 1. Send SMS
 * 2. Call Emergency Contact
 * 3. Ring for 20 Seconds
 * 4. Hang Up
 **************************************************************/
bool GSM::sendSOS(const String &phoneNumber,
                  const String &message)
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("STARTING SOS PROCEDURE");
    Serial.println("========================================");

    if (!isModuleReady())
    {
        Serial.println("SIM800L Not Ready");
        return false;
    }

    if (!isNetworkAvailable())
    {
        Serial.println("Network Not Available");
        return false;
    }

    Serial.println("Sending Emergency SMS...");

    if (!sendSMS(phoneNumber, message))
    {
        Serial.println("Emergency SMS Failed");
        return false;
    }

    Serial.println("Emergency SMS Sent Successfully");

    delay(3000);

    if (!makeCall(phoneNumber))
    {
        Serial.println("Unable To Call Emergency Contact");
        return false;
    }

    Serial.println("Calling...");

    delay(20000);

    hangUp();

    Serial.println("SOS Procedure Completed");

    return true;
}