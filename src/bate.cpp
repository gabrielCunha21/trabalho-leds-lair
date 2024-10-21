// #include <Arduino.h>
// #include <TFT_eSPI.h>      // Biblioteca para o display TFT
// #include <SPI.h>          // Biblioteca para comunicação SPI

// TFT_eSPI tft = TFT_eSPI();  // Inicializa o display TFT

// // Configurações de leitura do nível da bateria
// const int batteryPin = GPIO_NUM_1;  // Pino analógico onde a bateria está conectada (GPIO 35)
// const int maxAnalogValue = 4095;  // Valor máximo da leitura analógica (12 bits)

// // Função para calcular a porcentagem da bateria
// int getBatteryPercentage() {
//   int analogValue = analogRead(batteryPin);
  
//   // Aqui, assumimos que o valor de leitura varia de 0 (bateria vazia) até maxAnalogValue (bateria cheia)
//   int batteryPercentage = map(analogValue, 0, maxAnalogValue, 0, 100);
  
//   // Limitar o valor entre 0 e 100 para evitar erros
//   batteryPercentage = constrain(batteryPercentage, 0, 100);
  
//   return batteryPercentage;
// }

// void setup() {
//   // Inicializa o monitor serial para debug
//   Serial.begin(115200);
  
//   // Inicializa o display TFT
//   tft.init();
//   tft.setRotation(1);  // Ajuste a orientação do display se necessário
  
//   // Define a cor de fundo e apaga a tela
//   tft.fillScreen(TFT_BLACK);
//   tft.fillScreen(TFT_BLACK);  // Limpa a tela
//   tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Cor do texto (branco com fundo preto)
//   tft.setTextSize(2); 
//   tft.setCursor(40, 30);

//   pinMode(GPIO_NUM_35, OUTPUT);
//   digitalWrite(GPIO_NUM_35, HIGH);

// }

// void loop() {
//   // Obtém a porcentagem da bateria
//   int batteryPercentage = getBatteryPercentage();
  
//   // Debug: imprime a porcentagem da bateria no monitor serial
//   Serial.print("Battery Percentage: ");
//   Serial.println(batteryPercentage);

//   // Atualiza a tela com a porcentagem
//    // Tamanho do texto

//   // Posiciona o texto no centro da tela
//   tft.setCursor(40, 60);  // Ajuste conforme o tamanho do seu display
//   tft.print("Battery: ");
//   tft.print(batteryPercentage);
//   tft.println("%");
  
//   // Espera por 1 segundo antes de atualizar novamente
//   delay(1000);
// }