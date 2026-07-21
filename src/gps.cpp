/*****************************************************************
 * gps.cpp
 * Smart Blind Stick
 * GPS Driver (Part 1)
 *****************************************************************/

#include "gps.h"

/***************************************************
 * Constructor
 ***************************************************/
GPS::GPS(HardwareSerial &serial)
{
    gpsSerial = &serial;

    latitude = 0.0;
    longitude = 0.0;
    altitude = 0.0;

    speed = 0.0;
    course = 0.0;

    satellites = 0;

    day = 0;
    month = 0;
    year = 0;

    hour = 0;
    minute = 0;
    second = 0;

    validLocation = false;
}

/***************************************************
 * Begin GPS
 ***************************************************/
void GPS::begin()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("GPS Module Initialized");
    Serial.println("Waiting for satellites...");
    Serial.println("=================================");
}

/***************************************************
 * Update GPS
 ***************************************************/
void GPS::update()
{
    while (gpsSerial->available())
    {
        char c = gpsSerial->read();

        gps.encode(c);
    }

    if (gps.location.isUpdated())
    {
        latitude = gps.location.lat();
        longitude = gps.location.lng();

        validLocation = gps.location.isValid();
    }

    if (gps.altitude.isUpdated())
    {
        altitude = gps.altitude.meters();
    }

    if (gps.speed.isUpdated())
    {
        speed = gps.speed.kmph();
    }

    if (gps.course.isUpdated())
    {
        course = gps.course.deg();
    }

    if (gps.satellites.isUpdated())
    {
        satellites = gps.satellites.value();
    }

    if (gps.date.isUpdated())
    {
        day = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
    }

    if (gps.time.isUpdated())
    {
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();
    }
}

/***************************************************
 * GPS Valid
 ***************************************************/
bool GPS::isValid()
{
    return validLocation;
}

/***************************************************
 * GPS Fix
 ***************************************************/
bool GPS::hasFix()
{
    return gps.location.isValid();
}

/***************************************************
 * Latitude
 ***************************************************/
double GPS::getLatitude()
{
    return latitude;
}

/***************************************************
 * Longitude
 ***************************************************/
double GPS::getLongitude()
{
    return longitude;
}

/***************************************************
 * Altitude
 ***************************************************/
double GPS::getAltitude()
{
    return altitude;
}

/***************************************************
 * Speed
 ***************************************************/
double GPS::getSpeed()
{
    return speed;
}

/***************************************************
 * Course
 ***************************************************/
double GPS::getCourse()
{
    return course;
}

/***************************************************
 * Satellites
 ***************************************************/
int GPS::getSatellites()
{
    return satellites;
}

/*****************************************************************
 * Date Functions
 *****************************************************************/

int GPS::getDay()
{
    return day;
}

int GPS::getMonth()
{
    return month;
}

int GPS::getYear()
{
    return year;
}

/*****************************************************************
 * Time Functions
 *****************************************************************/

int GPS::getHour()
{
    return hour;
}

int GPS::getMinute()
{
    return minute;
}

int GPS::getSecond()
{
    return second;
}

/*****************************************************************
 * Google Maps Link
 *****************************************************************/

String GPS::getGoogleMapsLink()
{
    if (!validLocation)
    {
        return "GPS Location Not Available";
    }

    String url = "https://www.google.com/maps?q=";

    url += String(latitude, 6);
    url += ",";
    url += String(longitude, 6);

    return url;
}

/*****************************************************************
 * Print Location
 *****************************************************************/

void GPS::printLocation()
{
    if (!validLocation)
    {
        Serial.println("GPS : No Fix");
        return;
    }

    Serial.println("--------------------------------");

    Serial.print("Latitude  : ");
    Serial.println(latitude, 6);

    Serial.print("Longitude : ");
    Serial.println(longitude, 6);

    Serial.print("Altitude  : ");
    Serial.print(altitude);
    Serial.println(" m");

    Serial.print("Speed     : ");
    Serial.print(speed);
    Serial.println(" km/h");

    Serial.print("Course    : ");
    Serial.print(course);
    Serial.println(" Degree");

    Serial.print("Satellites: ");
    Serial.println(satellites);

    Serial.println("--------------------------------");
}

/*****************************************************************
 * Print Date & Time
 *****************************************************************/

void GPS::printDateTime()
{
    Serial.print("Date : ");

    Serial.print(day);
    Serial.print("/");

    Serial.print(month);
    Serial.print("/");

    Serial.println(year);

    Serial.print("Time : ");

    if (hour < 10) Serial.print("0");
    Serial.print(hour);

    Serial.print(":");

    if (minute < 10) Serial.print("0");
    Serial.print(minute);

    Serial.print(":");

    if (second < 10) Serial.print("0");
    Serial.println(second);
}

/*****************************************************************
 * Print Complete GPS Status
 *****************************************************************/

void GPS::printStatus()
{
    Serial.println();
    Serial.println("========== GPS STATUS ==========");

    if (!validLocation)
    {
        Serial.println("GPS Fix : NOT AVAILABLE");
        Serial.println("===============================");
        return;
    }

    Serial.println("GPS Fix : OK");

    printLocation();

    printDateTime();

    Serial.print("Google Maps : ");
    Serial.println(getGoogleMapsLink());

    Serial.println("===============================");
}

/*****************************************************************
 * Return TinyGPS++ Object
 *****************************************************************/

TinyGPSPlus& GPS::getGPS()
{
    return gps;
}