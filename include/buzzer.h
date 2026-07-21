#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer
{
private:
    uint8_t pin;
    bool state;
    unsigned long previousMillis;
    unsigned long interval;
    bool enableBlink;

public:
    Buzzer(uint8_t buzzerPin);

    void begin();
    void update();

    void stop();
    void continuous();

    void slowBeep();
    void fastBeep();

    void obstacleAlert(float distance);
};

#endif