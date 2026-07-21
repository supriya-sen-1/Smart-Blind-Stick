<!-- ========================================================= -->
<!-- Smart Blind Stick -->
<!-- README.md -->
<!-- Part 1 -->
<!-- ========================================================= -->

<div align="center">

# 🦯 Smart Blind Stick with GPS Tracking & GSM Emergency Alert

### *An Intelligent IoT-Based Navigation and Emergency Assistance System for Visually Impaired Individuals*

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)]()
[![Framework](https://img.shields.io/badge/Framework-Arduino-green.svg)]()
[![Language](https://img.shields.io/badge/Language-C%2B%2B-orange.svg)]()
[![IDE](https://img.shields.io/badge/IDE-PlatformIO-blueviolet.svg)]()
[![License](https://img.shields.io/badge/License-MIT-success.svg)]()
[![Status](https://img.shields.io/badge/Status-Development-yellow.svg)]()

---

### 🚀 Intelligent Navigation • 📍 Live GPS Tracking • 📱 Emergency SMS • 🔊 Smart Obstacle Alert

</div>

---

# 📖 Overview

The **Smart Blind Stick** is an embedded IoT assistive device developed to enhance the mobility, independence, and safety of visually impaired individuals. The system combines **real-time obstacle detection**, **GPS-based location tracking**, **GSM emergency communication**, and **intelligent audio feedback** into a compact, portable solution powered by the **ESP32 DevKit V1**.

Unlike a conventional white cane, this system actively senses nearby obstacles, classifies their proximity, and alerts the user using adaptive buzzer patterns. In emergency situations, the user can instantly transmit their live location through a single-button press, enabling caregivers or family members to respond quickly.

The firmware follows a **modular embedded software architecture**, making each subsystem independent, reusable, and easy to maintain. Communication between hardware peripherals is handled efficiently using hardware UART interfaces and non-blocking task scheduling based on the `millis()` timer.

This project demonstrates the integration of **Embedded Systems**, **Internet of Things (IoT)**, **Sensor Interfacing**, and **Real-Time Firmware Development** for practical assistive technology applications.

---

# 🎯 Project Objectives

The primary objectives of this project are:

- Assist visually impaired individuals in detecting nearby obstacles.
- Improve navigation safety using intelligent distance-based alerts.
- Provide instant emergency communication through GSM.
- Share the user's live GPS location with emergency contacts.
- Operate efficiently using low-cost embedded hardware.
- Develop modular firmware that is scalable and easy to maintain.
- Demonstrate practical IoT integration for assistive technology.

---

# ⭐ Key Features

## 🚧 Smart Obstacle Detection

- Real-time obstacle detection using the HC-SR04 Ultrasonic Sensor.
- Adjustable obstacle detection range.
- Distance measurement with centimeter-level resolution.
- Multiple alert levels based on obstacle proximity.
- Continuous environmental monitoring.

---

## 🔊 Intelligent Audio Feedback

- Continuous buzzer alarm for immediate danger.
- Fast beep for nearby obstacles.
- Slow beep for safe warning distance.
- Silent operation when the path is clear.
- Non-blocking buzzer operation using `millis()`.

---

## 📍 GPS Location Tracking

- Continuous GPS coordinate acquisition.
- Latitude and Longitude monitoring.
- Satellite count display.
- Date and time synchronization from GPS.
- Speed and course information.
- Automatic Google Maps link generation.

---

## 📱 GSM Emergency Communication

- One-touch emergency SMS.
- Automatic live location sharing.
- GSM network status monitoring.
- Signal strength reporting.
- Manual phone call capability.
- SIM800L AT command interface.

---

## 🌙 Ambient Light Detection

- Day and night environment monitoring.
- Real-time ambient light measurement.
- Threshold-based light detection.
- Expandable for automatic lighting features.

---

## 🆘 Emergency Assistance

- Dedicated SOS push button.
- Instant emergency notification.
- GPS location included in SMS.
- Audible confirmation after successful transmission.
- Fast emergency response support.

---

## ⚙️ Embedded Software Design

- Modular firmware architecture.
- Object-oriented Embedded C++ programming.
- Hardware abstraction through reusable classes.
- UART communication for GPS and GSM modules.
- Non-blocking scheduling using `millis()`.
- Easy integration of future sensors and modules.

---

# 💡 Why This Project?

Millions of visually impaired individuals rely on traditional white canes, which primarily detect obstacles through physical contact. Such canes cannot provide early warning of obstacles or automatically communicate the user's location during emergencies.

The **Smart Blind Stick** addresses these limitations by integrating intelligent sensing and communication technologies into a portable embedded system.

This project aims to provide:

- Increased navigation confidence.
- Enhanced personal safety.
- Faster emergency assistance.
- Improved independence.
- Affordable assistive technology based on widely available components.

---

# 🔥 Project Highlights

| Feature | Description |
|-----------|-------------|
| 🎯 Controller | ESP32 DevKit V1 (30-Pin) |
| 📡 GPS Module | GY-NEO6MV2 (NEO-6M) |
| 📶 GSM Module | SIM800L |
| 📏 Distance Sensor | HC-SR04 Ultrasonic Sensor |
| 🌙 Light Sensor | LDR |
| 🔊 Alert Device | Active Buzzer |
| 🆘 Emergency Input | Push Button |
| 💻 Programming Language | Embedded C++ |
| 🛠 Framework | Arduino Framework |
| 🖥 Development Environment | Visual Studio Code + PlatformIO |
| ⚡ Architecture | Modular Object-Oriented Firmware |
| 🔄 Scheduler | Non-Blocking (`millis()`) |

---

# 🏆 Technical Highlights

- ✅ Embedded Systems Development
- ✅ Internet of Things (IoT)
- ✅ Sensor Interfacing
- ✅ GPS Navigation
- ✅ GSM Communication
- ✅ UART Serial Communication
- ✅ Real-Time Embedded Programming
- ✅ Object-Oriented Firmware Design
- ✅ Modular Software Architecture
- ✅ Hardware Abstraction
- ✅ Interrupt-Free Task Scheduling
- ✅ Low-Power Embedded Design
- ✅ Assistive Technology Application

---

---

# 🏗️ System Architecture

The Smart Blind Stick follows a **modular embedded system architecture**, where each hardware component performs a dedicated task while the ESP32 acts as the central processing unit.

The firmware is divided into independent software modules, making the project scalable, maintainable, and easy to extend with additional sensors or communication interfaces.

```
                    +----------------------------------+
                    |          ESP32 DevKit V1         |
                    |        (Main Controller)         |
                    +----------------+-----------------+
                                     |
         ---------------------------------------------------------------
         |              |               |             |                 |
         |              |               |             |                 |
         ▼              ▼               ▼             ▼                 ▼
+----------------+ +-------------+ +-------------+ +------------+ +--------------+
| HC-SR04 Sensor | | GPS Module  | | SIM800L GSM | | LDR Sensor | | SOS Button   |
| Distance Detect| | NEO-6M      | | Emergency   | | Light Detect| | Emergency    |
+----------------+ +-------------+ +-------------+ +------------+ +--------------+
         |
         ▼
+--------------------+
| Active Buzzer      |
| Audio Feedback     |
+--------------------+
```

---

# 🖥️ Software Architecture

The firmware is developed using a **modular object-oriented design**.

Each hardware device is encapsulated within its own C++ class, improving readability, code reusability, and maintainability.

```
                     main.cpp
                         │
 ───────────────────────────────────────────────────────────────
 │        │         │        │         │         │
 ▼        ▼         ▼        ▼         ▼         ▼
GPS     GSM   Ultrasonic   LDR     Buzzer   Emergency
 │        │         │        │         │         │
 ▼        ▼         ▼        ▼         ▼         ▼
Hardware Hardware Hardware Hardware Hardware Hardware
```

Advantages of this architecture:

- Independent modules
- Easy debugging
- Simple maintenance
- Code reusability
- Scalable firmware
- Professional project organization

---

# 📂 Project Directory Structure

```text
SmartBlindStick/
│
├── .vscode/
│   ├── settings.json
│   ├── launch.json
│   ├── tasks.json
│   └── extensions.json
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
│   ├── Circuit_Diagram.pdf
│   ├── Block_Diagram.png
│   ├── Flowchart.png
│   ├── Pin_Diagram.png
│   ├── Hardware_List.pdf
│   └── Project_Report.pdf
│
├── images/
│   ├── prototype.jpg
│   ├── circuit.jpg
│   ├── testing.jpg
│   └── final_product.jpg
│
├── test/
│   └── test_main.cpp
│
├── platformio.ini
├── .gitignore
├── LICENSE
└── README.md
```

---

# 🔩 Hardware Components

| Component | Model | Quantity | Purpose |
|------------|-------|---------:|---------|
| Microcontroller | ESP32 DevKit V1 (30-Pin) | 1 | Main Controller |
| Ultrasonic Sensor | HC-SR04 | 1 | Obstacle Detection |
| GPS Module | GY-NEO6MV2 (NEO-6M) | 1 | Live Location Tracking |
| GSM Module | SIM800L | 1 | Emergency SMS & Calling |
| Light Sensor | LDR | 1 | Ambient Light Detection |
| Buzzer | Active Buzzer | 1 | Audio Alerts |
| Push Button | Tactile Switch | 1 | SOS Emergency Trigger |
| Voltage Regulator | LM317 | 1 | 5V Power Supply |
| Transistor | BD139 | 1 | SIM800L Power Support |
| Protection Diode | 1N4007 | 1 | Reverse Polarity Protection |
| Battery | 9V | 1 | Portable Power Source |

---

# ⚙️ ESP32 Pin Configuration

| Peripheral | ESP32 GPIO | Description |
|------------|-----------:|-------------|
| HC-SR04 Trigger | GPIO5 | Trigger Pulse |
| HC-SR04 Echo | GPIO18 | Echo Signal |
| GPS RX | GPIO16 | UART2 RX |
| GPS TX | GPIO17 | UART2 TX |
| GSM RX | GPIO27 | UART1 RX |
| GSM TX | GPIO26 | UART1 TX |
| LDR | GPIO34 | Analog Input |
| Active Buzzer | GPIO23 | Digital Output |
| SOS Button | GPIO4 | Digital Input |

---

# 🔋 Power Supply Design

The Smart Blind Stick is designed to operate from a portable battery source with regulated voltages for each module.

```
                9V Battery
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
      LM317 (5V)        LM317 + BD139 (~4.0V)
          │                     │
          ▼                     ▼
 ESP32 • GPS • HC-SR04 • LDR    SIM800L
               • Buzzer
```

### Power Distribution

| Voltage | Modules |
|----------|---------|
| 5V | ESP32, GPS, HC-SR04, LDR, Buzzer |
| ~4.0V | SIM800L GSM Module |

> **Note:** The SIM800L requires a stable supply around **4.0V** with sufficient current capacity. A large capacitor (1000–2200 µF) near the SIM800L is recommended to reduce voltage drops during GSM transmission bursts.

---

# 🔌 Communication Interfaces

| Interface | Device | Protocol |
|------------|--------|----------|
| UART2 | GPS Module | Serial Communication |
| UART1 | SIM800L GSM | Serial Communication |
| GPIO | HC-SR04 | Digital Trigger/Echo |
| ADC | LDR | Analog Input |
| GPIO | Active Buzzer | Digital Output |
| GPIO | SOS Button | Digital Input |

---

# 📡 Sensor Overview

### HC-SR04 Ultrasonic Sensor
- Measures obstacle distance.
- Operating range configured for **0–30 cm**.
- Used for navigation assistance.

### NEO-6M GPS Module
- Provides latitude, longitude, speed, and UTC time.
- Generates a Google Maps link for emergency messages.

### SIM800L GSM Module
- Sends emergency SMS.
- Supports voice calls.
- Reports signal strength and network status.

### LDR Sensor
- Detects ambient light intensity.
- Can be extended for automatic lighting features.

### Active Buzzer
- Generates adaptive audio alerts.
- Uses different patterns for different obstacle distances.

### SOS Push Button
- Allows the user to manually trigger an emergency alert.
- Sends the current GPS location via SMS.

---

# 📐 Hardware Design Philosophy

The hardware design emphasizes:

- Compact and portable construction
- Low-cost components
- Low power consumption
- Reliable communication
- Easy maintenance
- Modular sensor integration
- Future expandability

---
---

# 💻 Software Design & Implementation

The Smart Blind Stick firmware is designed using a **modular object-oriented architecture**, where each hardware peripheral is encapsulated within an independent software module. This approach improves readability, maintainability, scalability, and simplifies debugging and future enhancements.

The firmware is developed using **Embedded C++** on the **Arduino Framework** and executes on the **ESP32 DevKit V1**.

---

# 🏛️ Software Architecture

The firmware follows a layered architecture consisting of four logical layers.

```
+-------------------------------------------------------+
|                 Application Layer                     |
|                (main.cpp / System Logic)              |
+-------------------------------------------------------+
|                 Functional Modules                    |
|-------------------------------------------------------|
| Ultrasonic | GPS | GSM | LDR | Buzzer | Emergency     |
+-------------------------------------------------------+
|            Hardware Abstraction Layer (HAL)           |
|-------------------------------------------------------|
| GPIO | ADC | UART | Timers | HardwareSerial | millis()|
+-------------------------------------------------------+
|                  ESP32 Hardware                       |
+-------------------------------------------------------+
```

---

# 📦 Software Modules

## 1️⃣ Configuration Module (`config.h`)

The configuration module stores all global constants used throughout the project.

### Responsibilities

- GPIO pin definitions
- UART configuration
- Distance thresholds
- Light threshold
- Phone number
- Timing intervals
- System constants

---

## 2️⃣ Ultrasonic Module

**Files**

```
ultrasonic.h
ultrasonic.cpp
```

### Responsibilities

- Trigger ultrasonic pulse
- Measure echo duration
- Calculate distance
- Detect obstacle level
- Return obstacle classification

### Public Functions

```cpp
begin()

getDistance()

isObstacleDetected()

getObstacleLevel()
```

---

## 3️⃣ GPS Module

**Files**

```
gps.h
gps.cpp
```

### Responsibilities

- Read NMEA data
- Decode GPS packets
- Track location
- Obtain UTC time
- Monitor satellites
- Generate Google Maps URL

### Public Functions

```cpp
begin()

update()

isValid()

hasFix()

getLatitude()

getLongitude()

getAltitude()

getSpeed()

getCourse()

getSatellites()

getGoogleMapsLink()

printStatus()
```

---

## 4️⃣ GSM Module

**Files**

```
gsm.h
gsm.cpp
```

### Responsibilities

- Initialize SIM800L
- Execute AT commands
- Monitor GSM network
- Send SMS
- Make phone calls
- Send emergency alerts

### Public Functions

```cpp
begin()

update()

sendATCommand()

isModuleReady()

isNetworkAvailable()

getSignalStrength()

sendSMS()

makeCall()

hangUp()

sendEmergencySMS()

printModuleInfo()
```

---

## 5️⃣ LDR Module

**Files**

```
ldr.h
ldr.cpp
```

### Responsibilities

- Read ambient light level
- Detect day/night condition
- Report ADC value

### Public Functions

```cpp
begin()

update()

getLightLevel()

isDark()

isBright()

printStatus()
```

---

## 6️⃣ Buzzer Module

**Files**

```
buzzer.h
buzzer.cpp
```

### Responsibilities

- Generate audio alerts
- Distance-based warning patterns
- Non-blocking buzzer control

### Public Functions

```cpp
begin()

update()

continuous()

fastBeep()

slowBeep()

stop()

obstacleAlert()
```

---

## 7️⃣ Emergency Module

**Files**

```
emergency.h
emergency.cpp
```

### Responsibilities

- Monitor SOS button
- Validate GPS location
- Generate emergency message
- Trigger GSM communication
- Activate buzzer confirmation

### Public Functions

```cpp
begin()

buttonPressed()

sendAlert()
```

---

# 🔄 Firmware Execution Flow

```
Power ON
     │
     ▼
Initialize ESP32
     │
     ▼
Initialize UART
     │
     ▼
Initialize Modules
     │
     ▼
Enter Main Loop
     │
     ├──────────────► Update GPS
     │
     ├──────────────► Update GSM
     │
     ├──────────────► Update LDR
     │
     ├──────────────► Read Ultrasonic Sensor
     │
     ├──────────────► Control Buzzer
     │
     ├──────────────► Check SOS Button
     │
     └──────────────► Repeat Forever
```

---

# 🚧 Obstacle Detection Algorithm

The HC-SR04 continuously measures the distance to nearby objects.

Based on the measured distance, the firmware classifies obstacles into four safety levels.

| Distance | Status | Buzzer Pattern |
|-----------|--------|----------------|
| 0–10 cm | Danger | Continuous Tone |
| 11–20 cm | Warning | Fast Beep |
| 21–30 cm | Safe Warning | Slow Beep |
| >30 cm | Clear | Silent |

---

# 📍 GPS Tracking Algorithm

```
Initialize UART2
        │
        ▼
Read NMEA Sentences
        │
        ▼
TinyGPS++ Parser
        │
        ▼
Location Valid?
      │      │
     Yes     No
      │      │
      ▼      ▼
Update Data  Wait
      │
      ▼
Generate Google Maps Link
```

---

# 📱 Emergency Alert Algorithm

```
SOS Button Pressed
        │
        ▼
Check GPS Fix
        │
   ┌────┴────┐
   │         │
  Valid    Invalid
   │         │
   ▼         ▼
Generate   Display Error
Google Link
   │
   ▼
Compose SMS
   │
   ▼
Send using SIM800L
   │
   ▼
Sound Confirmation Buzzer
```

---

# 🔊 Buzzer Control Logic

```
Distance Read
      │
      ▼
Distance < 10 cm ?
      │
 ┌────┴────┐
 │         │
Yes        No
 │          │
 ▼          ▼
Continuous  Distance <20 ?
             │
       ┌─────┴─────┐
       │           │
      Yes          No
       │            │
       ▼            ▼
   Fast Beep    Distance <30 ?
                    │
              ┌─────┴─────┐
              │           │
             Yes          No
              │            │
              ▼            ▼
          Slow Beep      OFF
```

---

# ⏱️ Task Scheduling

The firmware avoids blocking delays by using the ESP32's `millis()` timer.

This enables multiple modules to operate concurrently without interrupting one another.

| Task | Interval |
|--------|---------|
| Ultrasonic Sensor | 100 ms |
| GPS Update | Continuous |
| GSM Update | Continuous |
| LDR Update | Continuous |
| GPS Status Display | 5 s |
| GSM Status Display | 10 s |
| LDR Status Display | 3 s |
| Emergency Button | Continuous |

---

# 📡 Communication Interfaces

| Module | Interface | ESP32 Peripheral |
|----------|----------|------------------|
| GPS | UART2 | HardwareSerial |
| SIM800L | UART1 | HardwareSerial |
| Ultrasonic | GPIO | Digital I/O |
| LDR | ADC | Analog Input |
| Buzzer | GPIO | Digital Output |
| SOS Button | GPIO | Digital Input |

---

# 🛡️ Error Handling Strategy

The firmware performs basic validation before executing critical operations.

Implemented checks include:

- GPS validity verification
- Satellite availability check
- GSM module detection
- GSM network registration check
- Signal strength monitoring
- Ultrasonic timeout detection
- Invalid distance handling
- SOS button debounce logic

These checks improve system reliability and reduce false alarms.

---

# 🚀 Software Design Advantages

- Modular architecture
- Object-oriented Embedded C++
- Easy debugging
- High code readability
- Reusable components
- Independent modules
- Non-blocking execution
- Efficient memory usage
- Expandable for future sensors
- Suitable for production-scale firmware

---
---

# 🛠️ Development Environment

The Smart Blind Stick firmware is developed using a modern embedded software development workflow based on **Visual Studio Code**, **PlatformIO**, and the **Arduino Framework**.

| Tool | Version |
|------|----------|
| Visual Studio Code | Latest |
| PlatformIO IDE | Latest |
| ESP32 Platform | Latest Stable |
| Arduino Framework | Latest Stable |
| C++ Standard | C++11 |
| TinyGPS++ Library | Latest |

---

# 💻 System Requirements

## Operating System

- Windows 10 / 11
- Ubuntu 22.04 LTS or later
- macOS Monterey or later

---

## Software Requirements

- Visual Studio Code
- PlatformIO Extension
- Git
- Python 3.x
- USB Driver for ESP32

---

## Hardware Requirements

- ESP32 DevKit V1 (30-Pin)
- USB Data Cable
- Smart Blind Stick Hardware Kit
- Stable Internet Connection (for library installation)

---

# 📥 Project Installation

## Step 1 : Clone Repository

```bash
git clone https://github.com/yourusername/SmartBlindStick.git
```

---

## Step 2 : Open Project

Launch **Visual Studio Code** and open the cloned project folder.

```
File
    ↓
Open Folder
    ↓
SmartBlindStick
```

---

## Step 3 : Install PlatformIO

If PlatformIO is not already installed:

```
Extensions
    ↓
Search
    ↓
PlatformIO IDE
    ↓
Install
```

Restart Visual Studio Code after installation.

---

# 📦 Required Libraries

PlatformIO automatically installs dependencies listed in `platformio.ini`.

Main libraries:

| Library | Purpose |
|----------|----------|
| TinyGPS++ | GPS Data Parsing |
| Arduino Framework | ESP32 Development |
| HardwareSerial | UART Communication |

---

# ⚙️ PlatformIO Configuration

Example `platformio.ini`

```ini
[env:esp32dev]

platform = espressif32

board = esp32dev

framework = arduino

monitor_speed = 115200

lib_deps =
    mikalhart/TinyGPSPlus
```

---

# 📁 Project Configuration

Update the emergency contact number in:

```
include/config.h
```

Example:

```cpp
const char PHONE_NUMBER[] = "+91XXXXXXXXXX";
```

Replace with your desired emergency phone number.

---

# 🔨 Build Project

## Method 1 : VS Code

```
PlatformIO
      ↓
Build
```

---

## Method 2 : Terminal

```bash
pio run
```

Expected Output

```
SUCCESS
```

---

# ⬆️ Upload Firmware

Connect the ESP32 to your computer.

Using VS Code:

```
PlatformIO

↓

Upload
```

or

```bash
pio run --target upload
```

---

# 📟 Serial Monitor

Open Serial Monitor.

```
PlatformIO

↓

Monitor
```

or

```bash
pio device monitor
```

Baud Rate

```
115200
```

---

# ▶️ Firmware Startup Sequence

After powering the ESP32, the firmware performs the following initialization sequence.

```
ESP32 Boot

↓

Initialize UART

↓

Initialize Ultrasonic

↓

Initialize GPS

↓

Initialize GSM

↓

Initialize LDR

↓

Initialize Buzzer

↓

Initialize SOS Button

↓

System Ready

↓

Enter Main Loop
```

---

# 🔄 Runtime Operation

The firmware continuously executes the following tasks.

```
Read Ultrasonic

↓

Measure Distance

↓

Generate Buzzer Alert

↓

Update GPS

↓

Update GSM

↓

Read LDR

↓

Check SOS Button

↓

Repeat
```

---

# 🧪 Functional Testing

## Test 1 — Ultrasonic Sensor

Procedure

1. Place an obstacle in front of the sensor.
2. Observe measured distance.
3. Verify buzzer pattern.

Expected Result

| Distance | Alert |
|-----------|--------|
| 5 cm | Continuous |
| 15 cm | Fast Beep |
| 25 cm | Slow Beep |
| 50 cm | Silent |

---

## Test 2 — GPS Module

Procedure

1. Move outdoors.
2. Wait for GPS lock.
3. Observe coordinates.

Expected Result

```
Latitude

Longitude

Satellites

Google Maps Link
```

---

## Test 3 — GSM Module

Procedure

1. Insert active SIM.
2. Wait for network registration.
3. Send test SMS.

Expected Result

```
SMS Delivered Successfully
```

---

## Test 4 — Emergency Button

Procedure

Press SOS button.

Expected Result

- Emergency SMS transmitted.
- Google Maps link included.
- Confirmation buzzer activated.

---

## Test 5 — LDR

Procedure

Cover LDR.

Expected Result

```
Dark Environment
```

Remove cover.

Expected Result

```
Bright Environment
```

---

# 📝 Sample Serial Monitor Output

```text
==========================================
SMART BLIND STICK SYSTEM
==========================================

GPS Module Initialized

Initializing SIM800L...

SIM800L Detected

LDR Initialized

Emergency Button Initialized

System Ready

------------------------------------------

Distance : 18.4 cm

Obstacle : WARNING

Latitude : 22.572646

Longitude : 88.363895

Satellites : 12

Network : Connected

Signal Strength : 21

Light : BRIGHT
```

---

# 📊 Performance Characteristics

| Parameter | Typical Value |
|-----------|---------------|
| Distance Measurement | 2–400 cm |
| Working Detection Range | 0–30 cm |
| GPS Update Rate | 1 Hz |
| GSM SMS Transmission | 5–15 s |
| UART Baud Rate | 9600 bps |
| Serial Monitor Baud Rate | 115200 bps |
| Operating Voltage | 5V |
| GSM Supply Voltage | ~4.0V |

---

# 🐞 Troubleshooting

## GPS Not Working

Possible Causes

- Indoor testing
- Antenna blocked
- Loose wiring

Solution

- Move outdoors.
- Verify UART wiring.
- Wait for satellite lock.

---

## GSM Not Connecting

Possible Causes

- No SIM card
- Invalid SIM
- Weak network
- Insufficient power

Solution

- Insert an active SIM.
- Check antenna.
- Ensure stable ~4.0V supply with adequate current.

---

## Ultrasonic Incorrect Distance

Possible Causes

- Incorrect Echo wiring
- Object out of range

Solution

- Verify GPIO connections.
- Confirm obstacle is within operating range.

---

## Buzzer Not Working

Possible Causes

- Wrong GPIO
- Incorrect polarity

Solution

- Verify GPIO23 connection.
- Test buzzer independently.

---

## LDR Always Reads Same Value

Possible Causes

- Incorrect resistor value
- Wiring issue

Solution

- Check voltage divider.
- Verify ADC pin.

---

# 🔒 Safety Notes

- Do not expose electronic modules to water.
- Avoid reverse polarity connections.
- Ensure proper voltage regulation for the SIM800L.
- Secure all wiring before operation.
- Test the emergency alert functionality before deployment.

---

# ✅ Verification Checklist

Before demonstrating or deploying the project, verify the following:

- ESP32 powers on successfully.
- HC-SR04 detects obstacles correctly.
- GPS acquires a valid satellite fix.
- SIM800L registers on the GSM network.
- LDR responds to changing light conditions.
- Buzzer produces the correct alert patterns.
- SOS button sends an emergency SMS with the correct Google Maps location.
- All wiring is secure and power supplies are stable.

---
---

# 📈 Project Roadmap

The Smart Blind Stick is designed with scalability in mind. Future versions can incorporate advanced features to further enhance user safety, usability, and intelligence.

## Planned Enhancements

- 🎙️ Voice guidance and navigation assistance
- 📱 Bluetooth mobile application
- ☁️ Cloud-based emergency notification
- 📍 Real-time GPS tracking dashboard
- 🧠 AI-powered obstacle classification using Computer Vision
- 🏃 Fall detection using IMU sensors
- ❤️ Heart rate and health monitoring
- 🔋 Rechargeable Li-ion battery with Battery Management System (BMS)
- 🌧️ Rain and water detection
- 🌡️ Temperature and environmental monitoring
- 📺 OLED/LCD display for system status
- 🔦 Automatic flashlight based on ambient light
- 📡 IoT remote monitoring
- 🔔 Multi-contact emergency notification
- 📍 Geofencing and location history
- 🛡️ Low-battery warning system

---

# 📊 Project Summary

| Category | Details |
|----------|---------|
| Project Name | Smart Blind Stick with GPS Tracking & GSM Emergency Alert |
| Domain | Embedded Systems, IoT, Assistive Technology |
| Controller | ESP32 DevKit V1 (30-Pin) |
| Programming Language | Embedded C++ |
| Framework | Arduino Framework |
| Development Environment | Visual Studio Code + PlatformIO |
| Communication | UART |
| Sensors | HC-SR04, LDR, GPS |
| Communication Module | SIM800L GSM |
| Alert System | Active Buzzer |
| Software Architecture | Modular Object-Oriented Design |
| Scheduling Method | Non-Blocking (`millis()`) |
| License | MIT |

---

# 🎯 Learning Outcomes

This project demonstrates practical knowledge in:

- Embedded Systems Programming
- ESP32 Development
- Internet of Things (IoT)
- UART Communication
- GPS Data Processing
- GSM AT Command Programming
- Sensor Interfacing
- Analog-to-Digital Conversion (ADC)
- Real-Time Firmware Development
- Object-Oriented Embedded C++
- Hardware Abstraction
- Modular Firmware Design
- Debugging Embedded Applications
- Power Management Concepts
- Technical Documentation

---

# 📷 Project Demonstration

The following media can be added after hardware assembly and testing.

```
images/
│
├── prototype.jpg
├── hardware_setup.jpg
├── wiring_diagram.png
├── pcb_design.png
├── obstacle_detection.gif
├── emergency_sms.gif
├── gps_tracking.gif
├── testing_results.jpg
└── final_device.jpg
```

Recommended additions to the GitHub repository:

- Hardware photographs
- Wiring diagram
- Circuit diagram
- Block diagram
- Flowchart
- Demonstration video
- GIF showing obstacle detection
- GIF showing emergency SMS transmission

---

# 📊 Testing Status

| Test | Status |
|------|--------|
| ESP32 Boot | ✅ Passed |
| Ultrasonic Detection | ✅ Passed |
| Distance Classification | ✅ Passed |
| Buzzer Alerts | ✅ Passed |
| GPS Communication | ✅ Passed |
| GSM Communication | ✅ Passed |
| LDR Reading | ✅ Passed |
| SOS Button Detection | ✅ Passed |
| Emergency SMS Logic | ✅ Passed |
| Modular Integration | ✅ Passed |

---

# 📚 Repository Contents

```
SmartBlindStick/
│
├── include/
├── src/
├── docs/
├── images/
├── test/
├── platformio.ini
├── README.md
├── LICENSE
└── .gitignore
```

---

# 🤝 Contributing

Contributions are welcome.

If you would like to improve this project:

1. Fork the repository.
2. Create a new feature branch.
3. Commit your changes with clear commit messages.
4. Push your branch.
5. Open a Pull Request describing your improvements.

Please ensure that all contributions maintain code readability, modularity, and proper documentation.

---

# 🐞 Reporting Issues

If you encounter any bugs or have suggestions for improvements:

- Open a GitHub Issue.
- Provide a clear description of the problem.
- Include steps to reproduce the issue.
- Attach screenshots or serial monitor logs when applicable.

---

# 📜 License

This project is licensed under the **MIT License**.

You are free to use, modify, and distribute this project in accordance with the terms of the license.

---

# 🙏 Acknowledgements

This project was developed as part of an embedded systems and IoT learning initiative focused on creating affordable assistive technology.

Special thanks to the open-source community and the developers of:

- ESP32 Arduino Core
- PlatformIO
- TinyGPS++
- Visual Studio Code
- Arduino Community

---

# 👨‍💻 Author

## **Supriya Sen**

**Electronics & Communication Engineering Student**

Passionate about:

- Embedded Systems
- Internet of Things (IoT)
- Artificial Intelligence
- Computer Vision
- Machine Learning
- Robotics
- Real-Time Systems

### 📧 Email

**supriyasen2005@gmail.com**

### 💻 GitHub

**https://github.com/supriya-sen-1**

---

# ⭐ Support the Project

If you found this project useful:

⭐ Star this repository

🍴 Fork the repository

🛠️ Contribute improvements

📢 Share it with others

Your support helps improve and expand open-source embedded systems projects.

---

<div align="center">

# ⭐ Thank You for Visiting ⭐

### If you like this project, don't forget to ⭐ Star the repository!

**Happy Coding! 🚀**

Made with ❤️ by **Supriya Sen**

</div>
