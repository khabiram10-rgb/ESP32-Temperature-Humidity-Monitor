🌡️ ESP32 Temperature and Humidity Monitoring System

An IoT-based temperature and humidity monitoring system using ESP32, DHT11, and Adafruit IO. This project monitors environmental conditions, uploads sensor readings to the cloud, and activates a buzzer when the temperature exceeds a defined threshold.

📸 Project Overview

<!-- Replace the image path below with your uploaded project image --> !ESP32 Temperature and Humidity Monitoring System

✨ Features
Real-time temperature and humidity monitoring
Wireless connectivity using ESP32 Wi-Fi
Cloud data logging using Adafruit IO
Automatic buzzer alert based on temperature thresholds
FreeRTOS multitasking for sensing, display, and alerts
Sensor readings displayed through the Serial Monitor
🛠️ Components Required
ESP32 development board
DHT11 temperature and humidity sensor
Buzzer
Breadboard and jumper wires
USB cable
🔌 Hardware Connections
Component	Pin	ESP32 Connection
DHT11	VCC	3.3V
DHT11	DATA	GPIO 4
DHT11	GND	GND
Buzzer	Signal / IN	GPIO 25
Buzzer	GND	GND
💻 Source Code

The complete Arduino source code is available below.

📂 View Arduino Source Code

☁️ Adafruit IO Dashboard

Sensor readings are uploaded to Adafruit IO through Wi-Fi.

Temperature Feed: temperature
Humidity Feed: humidity
Upload interval: 10 seconds

<!-- Add your public dashboard URL here if available --> 📊 View Adafruit IO Dashboard

🚨 Alert Conditions
Temperature Condition	Buzzer Status
Above 30°C	ON
Between 29°C and 30°C	Maintains previous state
Below 29°C	OFF
⚙️ Software and Libraries
Arduino IDE
ESP32 Arduino Core
DHT sensor library
Adafruit IO Arduino library
FreeRTOS (ESP32)
🚀 Getting Started
Install Arduino IDE and the ESP32 board package.
Install the required DHT and Adafruit IO libraries.
Connect the DHT11 sensor to GPIO 4 and the buzzer to GPIO 25.
Configure Wi-Fi credentials and Adafruit IO credentials locally.
Upload the Arduino sketch to the ESP32.
Open the Serial Monitor at 115200 baud.
Verify sensor readings and check the Adafruit IO feeds.
🔐 Security

Never publish Wi-Fi passwords or Adafruit IO API keys in a public repository. Use placeholders in the source code and store actual credentials securely.

📄 License

This project is licensed under the MIT License.

Developed using ESP32, DHT11, Arduino IDE, and Adafruit IO.
