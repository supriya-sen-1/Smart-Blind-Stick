# Smart Blind Stick with GPS Tracking and GSM Emergency Alert

An intelligent IoT-based Smart Blind Stick designed to assist visually impaired individuals by detecting obstacles, monitoring ambient light, and providing emergency location sharing using GPS and GSM technologies.

---

# Features

- Real-time obstacle detection using HC-SR04 Ultrasonic Sensor
- Intelligent buzzer alerts based on obstacle distance
- GPS-based live location tracking
- One-button emergency SMS with Google Maps location
- Day/Night detection using LDR
- Modular Embedded C++ architecture
- ESP32-based high-performance controller
- Non-blocking firmware using `millis()`
- Professional modular project structure

---

# Hardware Components

| Component | Quantity |
|------------|----------|
| ESP32 DevKit V1 (30-Pin) | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| GY-NEO6MV2 GPS Module | 1 |
| SIM800L GSM Module | 1 |
| Active Buzzer | 1 |
| LDR Sensor | 1 |
| Push Button (SOS) | 1 |
| LM317 Voltage Regulator | 1 |
| BD139 Transistor | 1 |
| 1N4007 Diode | 1 |
| 9V Battery | 1 |

---

# Software

- PlatformIO
- VS Code
- Arduino Framework
- Embedded C++
- TinyGPS++ Library

---

# Project Structure

```text
SmartBlindStick/
│
├── include/
│   ├── config.h
│   ├── ultrasonic.h
│   ├── gps.h
│   ├── gsm.h
│   ├── ldr.h
│   ├── buzzer.h
│   └── emergency.h
│
├── src/
│   ├── main.cpp
│   ├── ultrasonic.cpp
│   ├── gps.cpp
│   ├── gsm.cpp
│   ├── ldr.cpp
│   ├── buzzer.cpp
│   └── emergency.cpp
│
├── docs/
│
├── images/
│
├── test/
│
├── platformio.ini
│
├── LICENSE
│
└── README.md
```

---

# ESP32 Pin Configuration

| Module | ESP32 Pin |
|----------|----------|
| HC-SR04 Trigger | GPIO5 |
| HC-SR04 Echo | GPIO18 |
| GPS RX | GPIO16 |
| GPS TX | GPIO17 |
| SIM800L RX | GPIO27 |
| SIM800L TX | GPIO26 |
| LDR | GPIO34 |
| Buzzer | GPIO23 |
| SOS Button | GPIO4 |

---

# System Workflow

1. ESP32 initializes all modules.
2. HC-SR04 continuously measures obstacle distance.
3. The buzzer changes its alert pattern according to the detected distance.
4. GPS continuously updates the current location.
5. GSM remains ready to send emergency messages.
6. LDR monitors ambient light.
7. When the SOS button is pressed:
   - Current GPS location is obtained.
   - A Google Maps link is generated.
   - An emergency SMS is sent to the predefined contact.

---

# Obstacle Detection Levels

| Distance | Alert |
|----------|-------|
| 0–10 cm | Continuous Buzzer |
| 11–20 cm | Fast Beep |
| 21–30 cm | Slow Beep |
| >30 cm | No Alert |

---

# Emergency SMS Format

```
******** EMERGENCY ********

Smart Blind Stick User Needs Immediate Assistance.

Location:
https://www.google.com/maps?q=Latitude,Longitude

Latitude : XX.XXXXXX

Longitude : YY.YYYYYY
```

---

# Build Instructions

## Clone Repository

```bash
git clone https://github.com/yourusername/SmartBlindStick.git
```

---

## Open Project

Open the project folder using Visual Studio Code.

---

## Install Dependencies

PlatformIO automatically installs the required packages.

Required library:

- TinyGPS++

---

## Build

```bash
PlatformIO: Build
```

or

```bash
pio run
```

---

## Upload

```bash
PlatformIO: Upload
```

or

```bash
pio run --target upload
```

---

## Monitor

```bash
pio device monitor
```

---

# Libraries Used

- Arduino Framework
- TinyGPS++
- HardwareSerial

---

# Future Improvements

- Voice guidance
- Bluetooth mobile application
- Cloud-based emergency notification
- Fall detection
- Rechargeable battery management
- OLED display
- AI-assisted obstacle classification

---

# Project Status

| Module | Status |
|----------|--------|
| Ultrasonic | Complete |
| GPS | Complete |
| GSM | Complete |
| LDR | Complete |
| Buzzer | Complete |
| Emergency Module | Complete |
| Main Integration | Complete |

Current software implementation is complete. Remaining work includes hardware integration, testing, documentation, and validation.

---

# License

This project is released under the MIT License.

---

# Author

**Supriya Sen**

Electronics and Communication Engineering

Embedded Systems • IoT • Artificial Intelligence • Computer Vision

---