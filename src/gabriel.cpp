// #include <ArduinoJson.h> // Biblioteca para manipulação de JSON
// #include <WiFi.h>
// #include <PubSubClient.h>
// #include "SensorQMI8658.hpp"
// #include <driver/timer.h> // Biblioteca para usar o timer de hardware
// #include <TFT_eSPI.h>
// #include <SPI.h>
// #include "img/conectando.h"
// #include "img/enviando.h"
// #include "img/reconectando.h"

// int cont;

// #define USE_WIRE

// #ifndef SENSOR_SDA
// #define SENSOR_SDA 11
// #endif

// #ifndef SENSOR_SCL
// #define SENSOR_SCL 10
// #endif

// #ifndef SENSOR_IRQ
// #define SENSOR_IRQ 38
// #endif

// #define IMU_CS 5

// // WiFi and MQTT settings
// const char* ssid = "leds-ifes";
// const char* password = "Ledslair@2024";
// const char* mqtt_server = "10.20.240.200";
// const uint16_t mqtt_port = 1883;
// const char* mqtt_topic_sen_gyr = "Topico/sensor/gyr";
// const char* mqtt_topic_sen_acc = "Topico/sensor/acc";

// WiFiClient espClient;
// PubSubClient client(espClient);

// TFT_eSPI tft = TFT_eSPI(); 

// SensorQMI8658 qmi;
// IMUdata gyr;
// IMUdata acc;

// // Timer settings
// hw_timer_t * timer = NULL;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
// volatile bool sendDataFlag = false;

// void IRAM_ATTR onTimer() {
//   portENTER_CRITICAL_ISR(&timerMux);
//   sendDataFlag = true;
//   portEXIT_CRITICAL_ISR(&timerMux);
// }

// void setup_wifi() {
//   delay(10);
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     tft.pushImage(0,0,280,240,conectando);
//   }

//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     if (client.connect("ESP32Client")) {
//       Serial.println("connected");
//     } else {
      
//       Serial.print(client.state());
//       tft.pushImage(0,0,280,240,reconectando);
//       delay(5000);
//     }
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   tft.init();
//   tft.setSwapBytes(true);
//   tft.setRotation(1);

//   setup_wifi();
//   client.setServer(mqtt_server, mqtt_port);

// #ifdef USE_WIRE
//   // Using WIRE
//   if (!qmi.begin(Wire, QMI8658_L_SLAVE_ADDRESS, SENSOR_SDA, SENSOR_SCL)) {
//     Serial.println("Failed to find QMI8658 - check your wiring!");
//     while (1) {
//       delay(1000);
//     }
//   }
// #else
//   if (!qmi.begin(IMU_CS)) {
//     Serial.println("Failed to find QMI8658 - check your wiring!");
//     while (1) {
//       delay(1000);
//     }
//   }
// #endif

//   // Configure gyroscope
//   qmi.configGyroscope(
//     SensorQMI8658::GYR_RANGE_64DPS,
//     SensorQMI8658::GYR_ODR_896_8Hz,
//     SensorQMI8658::LPF_MODE_3,
//     true
//   );

//   qmi.enableGyroscope();

//   qmi.configAccelerometer(
//     SensorQMI8658::ACC_RANGE_4G,
//     SensorQMI8658::ACC_ODR_1000Hz,
//     SensorQMI8658::LPF_MODE_0,
//     true
//   );

//   qmi.enableAccelerometer();

//   Serial.println("Read data now...");

//   // Configurar o timer de hardware
//   timer = timerBegin(0, 80, true); // timer 0, prescaler 80, contando para cima
//   timerAttachInterrupt(timer, &onTimer, true); // anexa a função de interrupção
//   timerAlarmWrite(timer, 10000, true); // define o alarme para 20000 microssegundos (20 ms)
//   timerAlarmEnable(timer); // habilita o alarme
// }

// void loop() {
//   if (!client.connected()) {
//     reconnect();
//   }
//   client.loop();

//   if (sendDataFlag) {
//     portENTER_CRITICAL(&timerMux);
//     sendDataFlag = false;
//     portEXIT_CRITICAL(&timerMux);

//     tft.pushImage(0,0,280,240,enviando);

//     if (qmi.getDataReady()) {
//       if (qmi.getGyroscope(gyr.x, gyr.y, gyr.z)) {
//         // Cria um objeto JSON para armazenar os dados do giroscópio
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["Gyr"] = "";
//         jsonDoc["x"] = gyr.x;
//         jsonDoc["y"] = gyr.y;
//         jsonDoc["z"] = gyr.z;

//         // Serializa o JSON em uma string
//         char jsonBuffer[200];
//         serializeJson(jsonDoc, jsonBuffer);

//         // Envia o JSON via MQTT
//         client.publish(mqtt_topic_sen_gyr, jsonBuffer);
//       }

//       if (qmi.getAccelerometer(acc.x, acc.y, acc.z)) {
//         // Cria um objeto JSON para armazenar os dados do acelerômetro
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["Acc"] = "";
//         jsonDoc["x"] = acc.x;
//         jsonDoc["y"] = acc.y;
//         jsonDoc["z"] = acc.z;

//         // Serializa o JSON em uma string
//         char jsonBuffer[200];
//         serializeJson(jsonDoc, jsonBuffer);

//         // Envia o JSON via MQTT
//         client.publish(mqtt_topic_sen_acc, jsonBuffer);
//       }
//     }
//   }
// }
