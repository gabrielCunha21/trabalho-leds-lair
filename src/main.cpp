#include <ArduinoJson.h> // Biblioteca para manipulação de JSON
#include <WiFi.h>
#include <PubSubClient.h>
#include "SensorQMI8658.hpp"
#include <driver/timer.h> // Biblioteca para usar o timer de hardware
#include <TFT_eSPI.h>
#include <SPI.h>
#include "img/conectando.h"
#include "img/enviando.h"
#include "img/reconectando.h"

int cont,id;
unsigned long temp;
int batteryPercentage;

#define USE_WIRE

#ifndef SENSOR_SDA
#define SENSOR_SDA 11
#endif

#ifndef SENSOR_SCL
#define SENSOR_SCL 10
#endif

#ifndef SENSOR_IRQ
#define SENSOR_IRQ 38
#endif

#define IMU_CS 5

// WiFi and MQTT settings
const char* ssid = "leds-ifes";
const char* password = "Ledslair@2024";
const char* mqtt_server = "10.20.240.40";
const uint16_t mqtt_port = 1883;
const char* mqtt_topic_sen = "testeGabriel";

const int batteryPin = GPIO_NUM_1;  // Pino analógico onde a bateria está conectada (GPIO 35)
const int maxAnalogValue = 4095; 

WiFiClient espClient;
PubSubClient client(espClient);

TFT_eSPI tft = TFT_eSPI(); 

SensorQMI8658 qmi;
IMUdata gyr;
IMUdata acc;

// Timer settings
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
volatile bool sendDataFlag = false;
void leituraSensor();
int getBatteryPercentage();

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  sendDataFlag = true;
  //leituraSensor();
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  tft.pushImage(0,0,240,280,conectando);

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      
      tft.pushImage(0,0,240,280,reconectando);

      delay(500);
    }
  }
}

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(2);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  
  pinMode(GPIO_NUM_35, OUTPUT);
  digitalWrite(GPIO_NUM_35, HIGH);

  // pinMode(17, OUTPUT);
  // digitalWrite(17, HIGH);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

#ifdef USE_WIRE
  // Using WIRE
  if (!qmi.begin(Wire, QMI8658_L_SLAVE_ADDRESS, SENSOR_SDA, SENSOR_SCL)) {
    Serial.println("Failed to find QMI8658 - check your wiring!");
    while (1) {
      delay(1000);
    }
  }
#else
  if (!qmi.begin(IMU_CS)) {
    Serial.println("Failed to find QMI8658 - check your wiring!");
    while (1) {
      delay(1000);
    }
  }
#endif

  // Configure gyroscope
  qmi.configGyroscope(
    SensorQMI8658::GYR_RANGE_64DPS,
    SensorQMI8658::GYR_ODR_896_8Hz,
    SensorQMI8658::LPF_MODE_3,
    true
  );

  qmi.enableGyroscope();

  qmi.configAccelerometer(
    SensorQMI8658::ACC_RANGE_4G,
    SensorQMI8658::ACC_ODR_1000Hz,
    SensorQMI8658::LPF_MODE_0,
    true
  );

  qmi.enableAccelerometer();

  Serial.println("Read data now...");

  // Configurar o timer de hardware
  timer = timerBegin(0, 80, true); // timer 0, prescaler 80, contando para cima
  timerAttachInterrupt(timer, &onTimer, true); // anexa a função de interrupção
  
  timerAlarmWrite(timer, 20000, true); // define o alarme para 20000 microssegundos (20 ms)
  timerAlarmEnable(timer); // habilita o alarme
}

void loop() {
  if (sendDataFlag) {
    // Resetar o flag
    portENTER_CRITICAL(&timerMux);
    sendDataFlag = false;
    portEXIT_CRITICAL(&timerMux);
    // Realizar a leitura dos dados do sensor
    leituraSensor();
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  tft.pushImage(0,0,240,280,enviando);

  // batteryPercentage = getBatteryPercentage();

  // tft.setCursor(40, 60);  // Ajuste conforme o tamanho do seu display
  // tft.print("Battery: ");
  // tft.print(batteryPercentage);
  // tft.println("%");
}

void leituraSensor(){

  id = 0;
  temp = millis();

  if (qmi.getDataReady()) {
    if (qmi.getAccelerometer(acc.x, acc.y, acc.z) && qmi.getGyroscope(gyr.x, gyr.y, gyr.z)) {
      // Cria um objeto JSON para armazenar os dados do acelerômetro
      StaticJsonDocument<200> jsonDoc;
      // jsonDoc["id"] = id;
      // jsonDoc["acelX"] = acc.x;
      // jsonDoc["acelY"] = acc.y;
      // jsonDoc["acelZ"] = acc.z;
      // jsonDoc["girX"] = gyr.x;
      // jsonDoc["girY"] = gyr.y;
      // jsonDoc["girZ"] = gyr.z;
      //jsonDoc["tempoMs"] =  millis();
      String dataString = 
                        String(id) + "|" +
                        String(acc.x) + "|" +
                        String(acc.y) + "|" +
                        String(acc.z) + "|" +
                        String(gyr.x) + "|" +
                        String(gyr.y) + "|" +
                        String(gyr.z) + "|" +
                        String(millis());
                        
      jsonDoc["data"] = dataString;

      char jsonBuffer[200];
      serializeJson(jsonDoc, jsonBuffer);

      client.publish(mqtt_topic_sen, jsonBuffer);

    }
  }
}

int getBatteryPercentage() {
  int analogValue = analogRead(batteryPin);
  
  // Aqui, assumimos que o valor de leitura varia de 0 (bateria vazia) até maxAnalogValue (bateria cheia)
  int batteryPercentage = map(analogValue, 0, maxAnalogValue, 0, 100);
  
  // Limitar o valor entre 0 e 100 para evitar erros
  batteryPercentage = constrain(batteryPercentage, 0, 100);
  
  return batteryPercentage;
}