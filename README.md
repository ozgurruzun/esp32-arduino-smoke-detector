🔥 ESP32 + Arduino Smoke Detector System
<img width="1793" height="711" alt="diagram" src="https://github.com/user-attachments/assets/fc7e7ac8-bdde-40be-9337-a1ae0a406ea4" />

A dual-microcontroller based smoke detection system built using ESP32 and Arduino Uno.
The system detects smoke using an MQ-2 sensor and sends an SMS alert via Twilio API over WiFi.

📌 Project Overview

This project demonstrates:

Sensor data acquisition

Serial communication between two microcontrollers

WiFi-based API communication

SMS alert system using cloud API

The Arduino Uno reads smoke levels from the MQ-2 sensor.
If the threshold is exceeded, it notifies the ESP32 via Serial communication.
The ESP32 then connects to WiFi and sends an SMS alert using Twilio API.

🖼 System Diagram

Circuit diagram designed using Fritzing.

🧠 System Architecture
MQ-2 Sensor → Arduino Uno → Serial Communication → ESP32 → Twilio API → SMS Alert
🛠 Hardware Components

ESP32 Dev Module

Arduino Uno

MQ-2 Smoke Sensor

Buzzer

Jumper Wires

Breadboard

🔌 Communication Protocol

Arduino → ESP32 communication via UART (Serial)

Baud Rate: 9600

Simple trigger message: "SMOKE_DETECTED"

🌐 Network & API

WiFi connection handled by ESP32

HTTPS POST request sent to Twilio REST API

SMS alert sent to predefined phone number

📂 Project Structure
esp32-arduino-smoke-detector/
│
├── arduino/
│   └── arduino_smoke_detector.ino
│
├── esp32/
│   └── esp32_twilio_client.ino
│
├── diagram.png
└── README.md
🚨 Alert Logic

Smoke level exceeds threshold

Arduino triggers alert

ESP32 receives signal

WiFi connection verified

SMS alert sent
