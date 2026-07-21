#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class Ultrasonic
{
private:
    uint8_t trigPin;
    uint8_t echoPin;

public:
    // Constructor
    Ultrasonic(uint8_t trig, uint8_t echo);

    // Initialize sensor
    void begin();

    // Get distance in centimeters
    float getDistance();

    // Check obstacle within a specified distance
    bool isObstacleDetected(float maxDistance);

    // Get obstacle level
    uint8_t getObstacleLevel();
};

#endif