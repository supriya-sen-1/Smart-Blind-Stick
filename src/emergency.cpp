/*****************************************************************
 * File    : emergency.cpp
 * Project : Smart Blind Stick
 *****************************************************************/

#include "emergency.h"

/*************************************************************
 * Constructor
 *************************************************************/
Emergency::Emergency(uint8_t pin)
{
    buttonPin = pin;
    lastButtonState = HIGH;
    lastDebounceTime = 0;
}

/*************************************************************
 * Initialize SOS Button
 *************************************************************/
void Emergency::begin()
{
    pinMode(buttonPin, INPUT_PULLUP);

    Serial.println("----------------------------------------");
    Serial.println("SOS Button Initialized");
    Serial.println("----------------------------------------");
}

/*************************************************************
 * Detect SOS Button Press
 *************************************************************/
bool Emergency::buttonPressed()
{
    bool currentState = digitalRead(buttonPin);

    if (currentState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
        if (lastButtonState == HIGH && currentState == LOW)
        {
            lastButtonState = currentState;
            return true;
        }
    }

    lastButtonState = currentState;

    return false;
}

/*************************************************************
 * Send Emergency Alert
 *************************************************************/
bool Emergency::sendAlert(GPS &gps,
                          GSM &gsm,
                          Buzzer &buzzer,
                          const String &phoneNumber)
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("         SOS BUTTON PRESSED");
    Serial.println("========================================");

    //----------------------------------------------------------
    // Check GPS Fix
    //----------------------------------------------------------

    if (!gps.isValid())
    {
        Serial.println("GPS Fix Not Available");

        buzzer.fastBeep();

        return false;
    }

    //----------------------------------------------------------
    // Build Emergency Message
    //----------------------------------------------------------

    String message;

    message += "******** EMERGENCY ALERT ********\n\n";

    message += "Smart Blind Stick User\n";
    message += "Needs Immediate Assistance.\n\n";

    message += "Current Location:\n";
    message += gps.getGoogleMapsLink();

    message += "\n\nLatitude : ";
    message += String(gps.getLatitude(), 6);

    message += "\nLongitude : ";
    message += String(gps.getLongitude(), 6);

    //----------------------------------------------------------
    // Send SOS (SMS + Call)
    //----------------------------------------------------------

    bool success = gsm.sendSOS(phoneNumber, message);

    if (success)
    {
        Serial.println();
        Serial.println("========================================");
        Serial.println("SOS ALERT COMPLETED");
        Serial.println("========================================");

        Serial.print("Emergency Contact : ");
        Serial.println(phoneNumber);

        Serial.println();

        Serial.println("Google Maps Location:");
        Serial.println(gps.getGoogleMapsLink());

        buzzer.continuous();
        delay(3000);
        buzzer.stop();

        return true;
    }

    //----------------------------------------------------------
    // Failed
    //----------------------------------------------------------

    Serial.println();
    Serial.println("SOS Alert Failed");

    buzzer.fastBeep();

    return false;
}