#ifndef LDR_H
#define LDR_H

#include <Arduino.h>

class LDR
{
private:

    uint8_t pin;
    int threshold;
    int lightValue;

public:

    // Constructor
    LDR(uint8_t sensorPin, int thresholdValue);

    // Initialize LDR
    void begin();

    // Read Sensor
    void update();

    // Return Raw ADC Value
    int getLightLevel();

    // Check Dark Condition
    bool isDark();

    // Check Bright Condition
    bool isBright();

    // Print Sensor Information
    void printStatus();
};

#endif