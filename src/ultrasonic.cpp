#include "ultrasonic.h"
#include "config.h"

Ultrasonic::Ultrasonic(uint8_t trig, uint8_t echo)
{
    trigPin = trig;
    echoPin = echo;
}

void Ultrasonic::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    digitalWrite(trigPin, LOW);
}

float Ultrasonic::getDistance()
{
    // Clear trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // 10 µs trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Faster timeout (15 ms)
    long duration = pulseIn(echoPin, HIGH, 15000);

    // No echo received
    if (duration == 0)
        return -1;

    // Distance in cm
    return duration * 0.0343f / 2.0f;
}

bool Ultrasonic::isObstacleDetected(float maxDistance)
{
    float distance = getDistance();

    if (distance < 0)
        return false;

    return (distance <= maxDistance);
}

uint8_t Ultrasonic::getObstacleLevel()
{
    float distance = getDistance();

    if (distance < 0)
        return 0;

    if (distance <= DANGER_DISTANCE_CM)
        return 3;

    if (distance <= WARNING_DISTANCE_CM)
        return 2;

    if (distance <= SAFE_DISTANCE_CM)
        return 1;

    return 0;
}