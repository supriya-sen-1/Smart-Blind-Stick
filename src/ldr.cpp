/*****************************************************************
 * ldr.cpp
 * Smart Blind Stick
 *****************************************************************/

#include "ldr.h"

LDR::LDR(uint8_t sensorPin, int thresholdValue)
{
    pin = sensorPin;
    threshold = thresholdValue;
    lightValue = 0;
}

/***************************************************
 * Initialize
 ***************************************************/
void LDR::begin()
{
    pinMode(pin, INPUT);

    Serial.println("LDR Initialized");
}

/***************************************************
 * Read Sensor
 ***************************************************/
void LDR::update()
{
    lightValue = analogRead(pin);
}

/***************************************************
 * Get Raw ADC Value
 ***************************************************/
int LDR::getLightLevel()
{
    return lightValue;
}

/***************************************************
 * Dark Detection
 ***************************************************/
bool LDR::isDark()
{
    return (lightValue < threshold);
}

/***************************************************
 * Bright Detection
 ***************************************************/
bool LDR::isBright()
{
    return (lightValue >= threshold);
}

/***************************************************
 * Print Status
 ***************************************************/
void LDR::printStatus()
{
    Serial.println();

    Serial.println("========== LDR STATUS ==========");

    Serial.print("ADC Value : ");
    Serial.println(lightValue);

    if (isDark())
    {
        Serial.println("Environment : DARK");
    }
    else
    {
        Serial.println("Environment : BRIGHT");
    }

    Serial.println("===============================");
}