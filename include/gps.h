#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>

class GPS
{
private:

    HardwareSerial *gpsSerial;
    TinyGPSPlus gps;

    double latitude;
    double longitude;
    double altitude;
    double speed;
    double course;

    int satellites;

    int day;
    int month;
    int year;

    int hour;
    int minute;
    int second;

    bool validLocation;

public:

    // Constructor
    GPS(HardwareSerial &serial);

    // Initialize GPS Module
    // UART is already configured in main.cpp
    void begin();

    // Update GPS Data
    void update();

    // GPS Status
    bool isValid();
    bool hasFix();

    // Location
    double getLatitude();
    double getLongitude();
    double getAltitude();

    // Movement
    double getSpeed();
    double getCourse();

    // Satellite Information
    int getSatellites();

    // Date
    int getDay();
    int getMonth();
    int getYear();

    // Time
    int getHour();
    int getMinute();
    int getSecond();

    // Google Maps Link
    String getGoogleMapsLink();

    // Print Functions
    void printLocation();
    void printDateTime();
    void printStatus();

    // Access TinyGPS++ Object
    TinyGPSPlus &getGPS();
};

#endif