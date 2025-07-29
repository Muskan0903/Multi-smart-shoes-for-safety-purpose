# Multi-smart-shoes-for-safety-purpose

A safety-focused wearable system embedded into footwear, designed to detect emergencies and automatically notify trusted contacts with the user's real-time location. This project uses GPS, GSM, Bluetooth, ultrasonic, pressure, and touch sensors to ensure prompt and smart alerting via SMS, phone call, and Bluetooth notification.

---

##  Features

-  **Emergency Activation**: Triggered via pressure sensor (foot impact) or touch input.
-  **GPS Tracking**: Sends real-time latitude and longitude using NEO-6M GPS.
-  **Automatic Call & SMS**: Sends emergency alerts with location via SIM800L GSM module.
-  **Proximity Buzzer**: Alerts when obstacles are detected within a certain distance.
-  **Bluetooth Support**: Sends GPS coordinates to a paired mobile app.
-  **Touch-Controlled Toggle**: Enable/disable ultrasonic detection & buzzer alerts.

---

## Hardware Components

| Component              | Description                      |
|------------------------|----------------------------------|
| Arduino Uno            | Microcontroller                  |
| SIM800L GSM Module     | Sends SMS and makes calls        |
| NEO-6M GPS Module      | Provides real-time location      |
| HC-05 Bluetooth Module | Sends data to mobile via Bluetooth |
| Ultrasonic Sensor      | Detects nearby obstacles         |
| Pressure Sensor        | Detects foot impact              |
| Touch Sensor           | Toggles alert system             |
| Buzzer                 | Audible proximity alert          |
| Power Supply           | Powers the entire setup          |

---

Working Principle

Pressure Sensor: Detects foot impact to determine user presence or movement.

Touch Sensor: Toggles the alert system on or off.

GPS Module: Reads current location coordinates.

SIM800L GSM Module:

Sends an SMS with a Google Maps location link.

Makes a call to a predefined emergency number.

Bluetooth Module (HC-05): Sends GPS data to a connected smartphone.

Ultrasonic Sensor + Buzzer: Provides obstacle detection and alerts via buzzer.

## ⚙️ Pin Configuration

```cpp
#define SIM_TX 8
#define SIM_RX 7
#define GPS_TX 11 
#define GPS_RX 12
#define HC05_TX 6
#define HC05_RX 5
#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER 3
#define PRESSURE_SENSOR A0
#define TOUCH_SENSOR 2
