/*****************************************************************
 * File    : gsm.h
 * Project : Smart Blind Stick
 * Board   : ESP32 DevKit V1
 *
 * Description:
 * SIM800L GSM Driver
 *****************************************************************/

#ifndef GSM_H
#define GSM_H

#include <Arduino.h>

class GSM
{
public:
    GSM(HardwareSerial &serial);

    void begin();
    void update();

    // Non-blocking periodic status check.
    // Call beginStatusCheck() to start it, call update() every loop()
    // to advance it. Safe to call beginStatusCheck() again while one
    // is already running - it will be ignored until the current one
    // finishes.
    void beginStatusCheck();
    bool isStatusCheckBusy();

    // Latest results from the last completed status check.
    bool lastModuleReady();
    bool lastNetworkAvailable();
    int  lastSignalStrength();

    // Blocking helpers - fine to use at boot (begin()) or for
    // one-shot, user-triggered actions (SOS button) where a few
    // seconds of blocking is acceptable. Do NOT call these from a
    // periodic loop() path.
    bool isModuleReady();
    bool isNetworkAvailable();
    int  getSignalStrength();
    void printModuleInfo();

    bool sendSMS(const String &phoneNumber, const String &message);
    bool makeCall(const String &phoneNumber);
    void hangUp();
    bool sendEmergencySMS(const String &phoneNumber, const String &gpsLink);
    bool sendSOS(const String &phoneNumber, const String &message);

private:
    HardwareSerial *gsmSerial;
    bool networkConnected;

    bool sendATCommand(const String &command,
                        const String &expectedResponse,
                        uint32_t timeout);

    // --- async status-check state machine ---
    enum class StatusState
    {
        IDLE,
        MODULE_SEND,
        MODULE_WAIT,
        NETWORK_SEND,
        NETWORK_WAIT,
        SIGNAL_SEND,
        SIGNAL_WAIT,
        DONE
    };

    StatusState statusState;
    unsigned long statusStepStart;
    String statusRxBuffer;

    bool resultModuleReady;
    bool resultNetworkAvailable;
    int  resultSignalStrength;

    void statusStateMachineStep();
    void printStatusReport();
};

#endif