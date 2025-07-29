## Multi-Smart Shoes for Safety Purpose
This is working prototype 
A **safety-focused wearable system** embedded into footwear, designed to detect emergencies and **automatically notify trusted contacts** with the user's real-time location.  
This IoT-enabled smart shoe integrates **GPS, GSM, Bluetooth, Ultrasonic, Pressure, and Touch Sensors** to ensure prompt and intelligent alerting through **SMS, phone call, and Bluetooth notifications**.

---

## Features

- **Emergency Activation**  
  Triggered via **pressure sensor** (foot impact) or **touch sensor** input.

- **Real-Time GPS Tracking**  
  Sends live **latitude and longitude** using **NEO-6M GPS Module**.

- **Automatic Call & SMS Alerts**  
  Uses **SIM800L GSM module** to:
  - Send an SMS with **Google Maps location link**
  - Make an emergency **phone call**

- **Proximity Buzzer Alert**  
  Activates a buzzer when obstacles are detected within a specific range via **ultrasonic sensor**.

- **Bluetooth Integration**  
  Sends GPS coordinates and sensor data to a connected mobile app via **HC-05 Bluetooth module**.

- **Touch-Controlled Toggle System**  
  Enable or disable buzzer and obstacle alerts using a **touch sensor**.

---

## Hardware Components

| Component              | Description                                 |
|------------------------|---------------------------------------------|
| Arduino Uno            | Microcontroller                             |
| SIM800L GSM Module     | Sends SMS and makes phone calls             |
| NEO-6M GPS Module      | Provides real-time location                 |
| HC-05 Bluetooth Module | Sends data to mobile via Bluetooth          |
| Ultrasonic Sensor      | Detects nearby obstacles                    |
| Pressure Sensor        | Detects foot impact                         |
| Touch Sensor           | Toggles alert system                        |
| Buzzer                 | Audible proximity alert                     |
| Power Supply           | External power for portability              |

---

## Working Principle

1. **Pressure Sensor**  
   Detects foot pressure to determine motion or emergency trigger.

2. **Touch Sensor**  
   Used as a toggle to enable or disable the proximity alert system.

3. **GPS Module**  
   Reads and transmits real-time **latitude and longitude**.

4. **SIM800L GSM Module**  
   - Sends **SMS with coordinates** and Google Maps link  
   - Initiates **emergency phone call** to predefined contact

5. **Bluetooth Module (HC-05)**  
   Sends GPS and sensor data to a mobile app developed using **MIT App Inventor**.

6. **Ultrasonic Sensor + Buzzer**  
   Alerts the user if an object is detected within the unsafe proximity threshold.

---

## Pin Configuration

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

