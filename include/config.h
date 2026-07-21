#ifndef CONFIG_H
#define CONFIG_H

/****************************************************************
 * Project : Smart Blind Stick with GPS & GSM
 * Board   : ESP32 DevKit V1 (30-Pin)
 * Author  : Supriya Sen
 ****************************************************************/

/******************** GPS Module (NEO-6M) **********************/
#define GPS_RX_PIN         16      // GPS TX -> ESP32 GPIO16 (RX2)
#define GPS_TX_PIN         17      // GPS RX -> ESP32 GPIO17 (TX2)

/******************** SIM800L GSM Module ***********************/
#define GSM_RX_PIN         27      // SIM800L TX -> ESP32 GPIO27
#define GSM_TX_PIN         26      // SIM800L RX -> ESP32 GPIO26

/******************** HC-SR04 Ultrasonic Sensor ****************/
#define TRIG_PIN           5
#define ECHO_PIN           18

/******************** LDR Sensor *******************************/
#define LDR_PIN            34

/******************** Active Buzzer ****************************/
#define BUZZER_PIN         23

/******************** SOS Push Button **************************/
#define SOS_BUTTON_PIN     4

/****************************************************************
 * Distance Settings (Centimeters)
 *
 * 0 - 15 cm  : Continuous Alarm
 * 16 - 20 cm : Very Fast Beep
 * 21 - 25 cm : Medium Beep
 * 26 - 30 cm : Slow Beep
 * >30 cm     : No Alarm
 ****************************************************************/

#define MAX_DISTANCE_CM        30
#define DANGER_DISTANCE_CM     15
#define WARNING_DISTANCE_CM    20
#define SAFE_DISTANCE_CM       30

/******************** LDR Threshold ****************************/
#define LDR_THRESHOLD      1800

/******************** Phone Number *****************************/
const char PHONE_NUMBER[] = "+917439563033";

/******************** Serial Monitor ***************************/
#define SERIAL_BAUD_RATE   115200

/****************************************************************
 * Task Update Intervals
 ****************************************************************/

// Ultrasonic Sensor (50 readings/second)
#define SENSOR_INTERVAL    20

// GPS Status
#define GPS_INTERVAL       1000

// GSM Status
#define GSM_INTERVAL       5000

// LDR Status
#define LDR_INTERVAL       500

#endif