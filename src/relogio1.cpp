// #include <TFT_eSPI.h>            // Inclui a biblioteca TFT
// #include <Wire.h>
// #include "SensorPCF85063.hpp"   // Inclui a biblioteca do sensor PCF85063
// #include "img/fundo.h"

// #define CS   10  // Pino Chip Select do TFT
// #define DC    9  // Pino Data/Command do TFT
// #define RST   8  // Pino Reset do TFT

// TFT_eSPI tft = TFT_eSPI();  // Inicializa o display TFT

// SensorPCF85063 rtc;  // Instancia do RTC

// void drawRotatedText(int x, int y, const char* text, int angle);

// void setup() {
//   Serial.begin(115200);
  
//   // Inicializa o display
//   tft.begin();
//   tft.fillScreen(TFT_BLACK);  // Fundo preto
//   tft.setSwapBytes(true);
//   tft.setRotation(1);

//   // Inicializa o RTC
//   if (!rtc.begin(Wire, PCF85063_SLAVE_ADDRESS, 11, 10)) {
//     Serial.println("Erro ao encontrar o PCF85063. Verifique a conexão.");
//     while (1) {
//       delay(1000);
//     }
//   }

//   // Define a data e a hora desejadas
// //   uint16_t ano = 2024;
// //   uint8_t mes = 10;
// //   uint8_t dia = 29;
// //   uint8_t hora = 13;
// //   uint8_t minuto = 30;
// //   uint8_t segundo = 0;

// //   // Configura a data e hora no RTC
// //   rtc.setDateTime(ano, mes, dia, hora, minuto, segundo);
// //   Serial.println("Data e hora configuradas com sucesso!");

// }

// void loop() {
  
//   tft.pushImage(-200,-200,280,240,fundo);

//   // Lê a data e hora atual do RTC
//   RTC_DateTime datetime = rtc.getDateTime();
  
//   // Limpa a área onde a hora será mostrada
//   // tft.fillScreen(TFT_BLACK);  // Apaga a área de texto (160x40 pixels)

//   // Formata a hora como uma string
//   char data[16];
//   char hora[16];
//   snprintf(data, sizeof(data), "%02d-%02d-%04d\n", datetime.day, datetime.month, datetime.year);
//   snprintf(hora, sizeof(hora), "%02d:%02d:%02d\n", datetime.hour, datetime.minute, datetime.second);


//   // Exibe a hora no display TFT
//   tft.setTextColor(TFT_BLACK);  // Define a cor do texto como branco
//   // tft.setCursor(60, 40);        // Ajuste conforme o tamanho do seu display
//   // tft.print(data);
//   // tft.setCursor(80, 80);        // Ajuste conforme o tamanho do seu display
//   // tft.print(hora); 

//   // drawRotatedText(40, 60, data, 0);
//   drawRotatedText(30, 30, "A", 0);            

//   delay(1000);  // Atualiza a cada segundo
// }

// void drawRotatedText(int x, int y, const char* text, int angle) {
//   float rad = angle * DEG_TO_RAD;  // Converte o ângulo para radianos
//   int16_t txtLength = strlen(text);
//   int16_t charSpacing = 12;

//   for (int i = 0; i < txtLength; i++) {
//     char c = text[i];

//     // Calcula as coordenadas rotacionadas para cada caractere
//     int16_t xOffset = cos(rad) * (i * charSpacing);
//     int16_t yOffset = sin(rad) * (i * charSpacing);

//     // Calcula a posição rotacionada do caractere
//     int16_t rotatedX = x + xOffset * cos(rad) - yOffset * sin(rad);
//     int16_t rotatedY = y + xOffset * sin(rad) + yOffset * cos(rad);

//     // Desenha cada caractere nas coordenadas calculadas
//     tft.drawChar(c, rotatedX, rotatedY, 2);  // Tamanho de fonte 2 (ajustável)
//   }
// }