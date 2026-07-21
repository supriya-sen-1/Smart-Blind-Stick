#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <Arduino.h>

#include "gps.h"
#include "gsm.h"
#include "buzzer.h"

class Emergency
{
private:
    // SOS Push Button Pin
    uint8_t buttonPin;

    // Button debounce variables
    bool lastButtonState;
    unsigned long lastDebounceTime;

    static const unsigned long DEBOUNCE_DELAY = 50;

public:
    // Constructor
    Emergency(uint8_t pin);

    // Initialize SOS button
    void begin();

    // Returns true when the SOS button is pressed
    bool buttonPressed();

    // Sends an emergency alert SMS
    bool sendAlert(GPS &gps,
                   GSM &gsm,
                   Buzzer &buzzer,
                   const String &phoneNumber);
};

#endif