#include <Arduino.h>
#include <DHT.h>
#include "AdafruitIO_WiFi.h"

// Adafruit IO credentials
#define IO_USERNAME  "KHABIRA"
#define IO_KEY       ""
// Wi-Fi credentials
#define WIFI_SSID ""
#define WIFI_PASS ""

// Sensor and buzzer
#define DHT_PIN 4
#define BUZZER_PIN 25
#define DHT_TYPE DHT11

const float ON_TEMP = 30.0;
const float OFF_TEMP = 29.0;

struct SensorData {
  float temp;
  float humidity;
};

DHT dht(DHT_PIN, DHT_TYPE);

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY,
                   WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *tempFeed = io.feed("temperature");
AdafruitIO_Feed *humFeed = io.feed("humidity");

QueueHandle_t displayQueue;
QueueHandle_t alertQueue;

void sensorTask(void *p) {
  SensorData d;
  unsigned long lastUpload = 0;

  while (true) {
    d.temp = dht.readTemperature();
    d.humidity = dht.readHumidity();

    if (!isnan(d.temp) && !isnan(d.humidity)) {
      xQueueOverwrite(displayQueue, &d);
      xQueueOverwrite(alertQueue, &d);

      // Upload every 10 seconds
      if (millis() - lastUpload >= 10000) {
        lastUpload = millis();

        if (io.status() == AIO_CONNECTED) {
          tempFeed->save(d.temp);
          humFeed->save(d.humidity);

          Serial.println("Data sent to Adafruit IO");
        } else {
          Serial.println("Adafruit IO disconnected");
        }
      }
    } else {
      Serial.println("DHT11 reading failed");
    }

    vTaskDelay(pdMS_TO_TICKS(2500));
  }
}

void displayTask(void *p) {
  SensorData d;

  while (true) {
    if (xQueueReceive(displayQueue, &d,
                      portMAX_DELAY) == pdTRUE) {
      Serial.print("Temp: ");
      Serial.print(d.temp);
      Serial.print(" C | Hum: ");
      Serial.println(d.humidity);
    }
  }
}

void alertTask(void *p) {
  SensorData d;
  bool alarm = false;

  while (true) {
    if (xQueueReceive(alertQueue, &d,
                      portMAX_DELAY) == pdTRUE) {
      if (d.temp > ON_TEMP) {
        alarm = true;
      }

      if (d.temp < OFF_TEMP) {
        alarm = false;
      }

      digitalWrite(BUZZER_PIN, alarm ? HIGH : LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  displayQueue = xQueueCreate(1, sizeof(SensorData));
  alertQueue = xQueueCreate(1, sizeof(SensorData));

  if (displayQueue == NULL || alertQueue == NULL) {
    Serial.println("Queue creation failed!");
    while (true) {
      delay(1000);
    }
  }

  // Connect to Adafruit IO
  Serial.println("Connecting to Adafruit IO...");
  io.connect();

  // Wait for connection while servicing MQTT
  while (io.status() < AIO_CONNECTED) {
    io.run();
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nAdafruit IO connected!");

  xTaskCreate(sensorTask, "Sensor", 4096, NULL, 2, NULL);
  xTaskCreate(displayTask, "Display", 3072, NULL, 1, NULL);
  xTaskCreate(alertTask, "Alert", 3072, NULL, 3, NULL);
}

void loop() {
  // Keep Wi-Fi and MQTT connection alive
  io.run();
  vTaskDelay(pdMS_TO_TICKS(10));
}
