ESP32 Temperature and Humidity Monitoring System
Project Overview

This project monitors temperature and humidity using an ESP32 and DHT11 sensor. Sensor readings are displayed through the Serial Monitor and uploaded to Adafruit IO using Wi-Fi. A buzzer provides a temperature-based alert.

Components Required
ESP32 development board
DHT11 temperature and humidity sensor
Buzzer
Jumper wires
Breadboard
USB cable
Hardware Connections
Component	Pin	ESP32 Connection
DHT11	VCC	3.3V
DHT11	DATA	GPIO 4
DHT11	GND	GND
Buzzer	Signal / IN	GPIO 25
Buzzer	GND	GND
Features
Real-time temperature monitoring
Humidity monitoring
Wi-Fi connectivity
Cloud data logging with Adafruit IO
Automatic buzzer alert based on temperature thresholds
FreeRTOS tasks for sensing, display, and alerts
Alert Conditions
Temperature above 30°C: Buzzer ON
Temperature below 29°C: Buzzer OFF
Between 29°C and 30°C: Previous alarm state is maintained
Software and Libraries
Arduino IDE
ESP32 Arduino Core
DHT sensor library
Adafruit IO Arduino library
Setup Instructions
Install Arduino IDE and the ESP32 board package.
Install the required sensor and Adafruit IO libraries.
Configure Wi-Fi and Adafruit IO credentials locally.
Connect the DHT11 sensor to GPIO 4 and the buzzer to GPIO 25.
Upload the sketch to the ESP32.
Open the Serial Monitor at 115200 baud.
Check the temperature and humidity feeds in Adafruit IO.
Security

Do not commit Wi-Fi passwords or Adafruit IO API keys to GitHub. Store credentials locally and use placeholder values in shared code.

License

MIT License
