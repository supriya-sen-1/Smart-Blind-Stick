/*****************************************************************
 * buzzer.cpp
 * Smart Blind Stick
 *****************************************************************/

#include "buzzer.h"
#include "config.h"

/***************************************************
 * Constructor
 ***************************************************/
Buzzer::Buzzer(uint8_t buzzerPin)
{
    pin = buzzerPin;
    state = LOW;
    previousMillis = 0;
    interval = 400;
    enableBlink = false;
}

/***************************************************
 * Initialize Buzzer
 ***************************************************/
void Buzzer::begin()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

/***************************************************
 * Update (Non-blocking)
 ***************************************************/
void Buzzer::update()
{
    if (!enableBlink)
        return;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        state = !state;
        digitalWrite(pin, state);
    }
}

/***************************************************
 * Stop Buzzer
 ***************************************************/
void Buzzer::stop()
{
    enableBlink = false;
    state = LOW;
    digitalWrite(pin, LOW);
}

/***************************************************
 * Continuous Alarm
 ***************************************************/
void Buzzer::continuous()
{
    enableBlink = false;
    state = HIGH;
    digitalWrite(pin, HIGH);
}

/***************************************************
 * Slow Beep
 ***************************************************/
void Buzzer::slowBeep()
{
    enableBlink = true;
    interval = 300;
}

/***************************************************
 * Fast Beep
 ***************************************************/
void Buzzer::fastBeep()
{
    enableBlink = true;
    interval = 70;
}

/***************************************************
 * Smart Distance-Based Obstacle Alert
 ***************************************************/
void Buzzer::obstacleAlert(float distance)
{
    // Guard clause for invalid or out-of-range maximum distances
    if (distance <= 0 || distance > MAX_DISTANCE_CM)
    {
        stop();
        return;
    }

    // Guard clause for critical danger zone
    if (distance <= DANGER_DISTANCE_CM)
    {
        continuous();
        return;
    }

    // Enable non-blocking blinking for the intermediate zone
    enableBlink = true;

    // Safely constrain the input distance to ensure map() behaves predictably
    int constrainedDistance = constrain((int)distance, (int)DANGER_DISTANCE_CM + 1, (int)MAX_DISTANCE_CM);

    // Dynamic beep speed mapping
    interval = map(
        constrainedDistance,
        (int)DANGER_DISTANCE_CM + 1,
        (int)MAX_DISTANCE_CM,
        60,
        400
    );
}