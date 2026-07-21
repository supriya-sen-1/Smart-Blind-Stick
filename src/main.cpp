/*****************************************************************
 * Project : Smart Blind Stick
 * File    : main.cpp
 * Board   : ESP32 DevKit V1 (30-Pin)
 * Framework : Arduino (PlatformIO)
 *
 * Features:
 * ---------------------------------------------------------------
 * ✓ Ultrasonic Obstacle Detection
 * ✓ Smart Buzzer Alert
 * ✓ GPS Location Tracking
 * ✓ GSM Emergency SMS
 * ✓ SOS Push Button
 * ✓ LDR Day/Night Detection
 *
 * Author : Supriya Sen
 *****************************************************************/

#include <Arduino.h>

#include "config.h"
#include "ultrasonic.h"
#include "gps.h"
#include "gsm.h"
#include "ldr.h"
#include "buzzer.h"
#include "emergency.h"

//==============================================================
// Hardware UART Configuration
//==============================================================

// UART2 -> GPS Module
HardwareSerial GPSSerial(2);

// UART1 -> SIM800L GSM Module
HardwareSerial GSMSerial(1);

//==============================================================
// Module Objects
//==============================================================

Ultrasonic sonar(TRIG_PIN, ECHO_PIN);
GPS gps(GPSSerial);
GSM gsm(GSMSerial);
LDR ldr(LDR_PIN, LDR_THRESHOLD);
Buzzer buzzer(BUZZER_PIN);
Emergency emergency(SOS_BUTTON_PIN);

//==============================================================
// Global Variables
//==============================================================

float distance = -1.0;

// Task Timers
unsigned long lastUltrasonicTime = 0;
unsigned long lastGPSStatusTime = 0;
unsigned long lastGSMStatusTime = 0;
unsigned long lastPrintTime = 0;

//==============================================================
// Setup
//==============================================================

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);

    Serial.println();
    Serial.println("==================================================");
    Serial.println("          SMART BLIND STICK SYSTEM");
    Serial.println("==================================================");

    //----------------------------------------------------------
    // UART Initialization
    //----------------------------------------------------------

    GPSSerial.begin(
        9600,
        SERIAL_8N1,
        GPS_RX_PIN,
        GPS_TX_PIN);

    GSMSerial.begin(
        38400,
        SERIAL_8N1,
        GSM_RX_PIN,
        GSM_TX_PIN);

    //----------------------------------------------------------
    // Initialize Modules
    //----------------------------------------------------------

    Serial.println("Initializing Modules...");

    sonar.begin();
    gps.begin();
    gsm.begin();

    Serial.println("Testing SIM800L...");

    GSMSerial.println("AT");
    delay(1000);

    while (GSMSerial.available())
    {
        Serial.write(GSMSerial.read());
    }

    ldr.begin();
    buzzer.begin();
    emergency.begin();

    Serial.println("All Modules Initialized Successfully.");

    Serial.println("==================================================");
    Serial.println("System Ready");
    Serial.println("==================================================");
}

//==============================================================
// Main Loop
//==============================================================

void loop()
{
    //----------------------------------------------------------
    // Continuous Background Updates
    //----------------------------------------------------------

   gps.update();
    ldr.update();
    buzzer.update();   // Drives the non-blocking beep timing — must run every loop cycle

    //----------------------------------------------------------
    // Ultrasonic Obstacle Detection (single source of truth)
    //----------------------------------------------------------

    if (millis() - lastUltrasonicTime >= SENSOR_INTERVAL)
    {
        lastUltrasonicTime = millis();

        // Read the sensor exactly once per interval
        distance = sonar.getDistance();

        if (distance < 0)
        {
            // Sensor timeout / no echo
            buzzer.stop();
        }
        else if (distance > MAX_DISTANCE_CM)
        {
            // No obstacle within range
            buzzer.stop();
        }
        else
        {
            // Obstacle within range -> buzzer reacts immediately,
            // beep rate scales smoothly from 400ms (at 30cm) to
            // 60ms (at 16cm), and goes fully continuous at <=15cm
            buzzer.obstacleAlert(distance);
        }

        // Throttled debug output (derives level from the distance
        // already read above -- does NOT re-trigger the sensor)
        if (millis() - lastPrintTime >= 200)
        {
            lastPrintTime = millis();

            Serial.print("Distance : ");

            if (distance < 0)
            {
                Serial.println("ERROR (no echo)");
            }
            else
            {
                Serial.print(distance);
                Serial.println(" cm");

                if (distance <= DANGER_DISTANCE_CM)
                {
                    Serial.println("Obstacle Level : DANGER");
                }
                else if (distance <= WARNING_DISTANCE_CM)
                {
                    Serial.println("Obstacle Level : WARNING");
                }
                else if (distance <= SAFE_DISTANCE_CM)
                {
                    Serial.println("Obstacle Level : SAFE WARNING");
                }
                else
                {
                    Serial.println("Obstacle Level : CLEAR");
                }
            }

            Serial.println("--------------------------------------------------");
        }
    }

    //----------------------------------------------------------
    // GPS Status
    //----------------------------------------------------------

    if (millis() - lastGPSStatusTime >= GPS_INTERVAL * 5)
    {
        lastGPSStatusTime = millis();
        gps.printStatus();
    }

    //----------------------------------------------------------
    // GSM Status
    //----------------------------------------------------------

    if (millis() - lastGSMStatusTime >= GSM_INTERVAL * 2)
    {
        lastGSMStatusTime = millis();
        //gsm.printModuleInfo();
    }

    //----------------------------------------------------------
    // SOS Emergency Button
    //----------------------------------------------------------

    if (emergency.buttonPressed())
    {
        Serial.println();
        Serial.println("==================================================");
        Serial.println("           SOS BUTTON PRESSED");
        Serial.println("==================================================");

        bool alertSent = emergency.sendAlert(
            gps,
            gsm,
            buzzer,
            PHONE_NUMBER
        );

        if (alertSent)
        {
            Serial.println("Emergency Alert Sent Successfully.");
        }
        else
        {
            Serial.println("Emergency Alert Failed.");
        }

        Serial.println("==================================================");
    }
}