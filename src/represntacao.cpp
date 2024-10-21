// #include <Arduino.h>
// #include <DabbleESP32.h>
// #include <ESP32Servo.h>

// TaskHandle_t sensor;

// Servo meuServo;

// #define CUSTOM_SETTINGS
// #define INCLUDE_GAMEPAD_MODULE

// //buzzer
// #define buzzer 46

// //Ponte H
// #define ENABLE_PIN 2
// #define MOTOR_A_IN1 37
// #define MOTOR_A_IN2 38
// #define PWM_PIN 36

// //servo
// #define SERVO_PIN 8
                                                                                                      
// // ultrassonicos dianteiros
// #define TRIGGER_PIN1  9
// #define ECHO_PIN1     10
// #define ECHO_PIN2     11
// #define ECHO_PIN3     12

// //ultrassonico traseiro
// #define TRIGGER_PIN2  13
// #define ECHO_PIN4     14

// //Encoder
// #define   encoderpin  4

// //Sensores de bateria
// #define pinbatesp       3
// #define pinbatmotor     1

// int  velocidade;
// float batesp, batmotor;
// long distance1, distance2, distance3, distance4, menor;
// float rpm;
// volatile byte pulsos;
// unsigned long timeold;
// bool motorPausado = false;
// unsigned long pausaMotorTempo;
// int speed,servoPosition;

// //define a quantidade de "furos" do encoder
// unsigned int pulsos_por_volta = 30;
// //define o raio da roda
// float raio_metros = 0.0175;
// //define o delay do ultrassonico em pico segundos
// int dly = 2000;
// //distancia para o robo parar quando ver um obstaculo
// int parar = 25;

// void contador()
// {
//   pulsos++;
// }

// void setup() {

//   Dabble.begin("Carrito");

//   pinMode(ENABLE_PIN, OUTPUT);
//   pinMode(MOTOR_A_IN1, OUTPUT);
//   pinMode(MOTOR_A_IN2, OUTPUT);
//   pinMode(PWM_PIN, OUTPUT);


//   digitalWrite(ENABLE_PIN, HIGH);
//   digitalWrite(MOTOR_A_IN1, LOW);
//   digitalWrite(MOTOR_A_IN2, LOW);
//   analogWrite(PWM_PIN, 0);

//   meuServo.attach(SERVO_PIN);
//   meuServo.write(90);

//   Serial.begin(115200); 
//   pinMode(TRIGGER_PIN1, OUTPUT);
//   pinMode(TRIGGER_PIN2, OUTPUT);
//   digitalWrite(TRIGGER_PIN1, LOW);
//   digitalWrite(TRIGGER_PIN2, LOW);
//   pinMode(ECHO_PIN1, INPUT);
//   pinMode(ECHO_PIN2, INPUT);
//   pinMode(ECHO_PIN3, INPUT);
//   pinMode(ECHO_PIN4, INPUT);
//   pinMode(encoderpin, INPUT);
//   pinMode(pinbatmotor, INPUT);
//   pinMode(pinbatesp, INPUT);

//   attachInterrupt(4, contador, FALLING);
//   pulsos = 0;
//   rpm = 0;
//   timeold = 0;


//   xTaskCreatePinnedToCore(
//                     sensorcode,   /* Task function. */
//                     "sensor",     /* name of task. */
//                     10000,       /* Stack size of task */
//                     NULL,        /* parameter of the task */
//                     1,           /* priority of the task */
//                     &sensor,      /* Task handle to keep track of created task */
//                     0);          /* pin task to core 0 */                  
//   delay(500); 

// } //end setup

// //Loop core 0
// void sensorcode( void * pvParameters ){

//   for(;;){

//   long duration;

//   //ultrassonicos dianteiros

//   //ultrasssonico 1
//   digitalWrite(TRIGGER_PIN1, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIGGER_PIN1, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIGGER_PIN1, LOW);

//   duration = pulseIn(ECHO_PIN1, HIGH, dly);
//   distance1 = duration * 0.034 / 2;

//   //ultrassonico 2
//   digitalWrite(TRIGGER_PIN1, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIGGER_PIN1, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIGGER_PIN1, LOW);

//   duration = pulseIn(ECHO_PIN2, HIGH, dly);
//   distance2 = duration * 0.034 / 2;

//   //ultrassonico 3
//   digitalWrite(TRIGGER_PIN1, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIGGER_PIN1, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIGGER_PIN1, LOW);

//   duration = pulseIn(ECHO_PIN3, HIGH, dly);
//   distance3 = duration * 0.034 / 2;

//   //ultrassonico traseiro
//   digitalWrite(TRIGGER_PIN2, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIGGER_PIN2, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIGGER_PIN2, LOW);

//   duration = pulseIn(ECHO_PIN4, HIGH, dly);
//   distance4 = duration * 0.034 / 2;
//   delay(10);

//   batesp = (100*analogRead(pinbatesp))/3550;
//   batmotor = (100*analogRead(pinbatmotor))/3550;

//   } //end loop core 0
// } // end void sensorcode

// //Loop core 1
// void loop() {

//   menor = 1000;

//   if (distance1 != 0 && distance1 < menor) {
//      menor = distance1;
//   }
//   if (distance2 != 0 && distance2 < menor) {
//     menor = distance2;
//   }
//   if (distance3 != 0 && distance3 < menor) {
//      menor = distance3;
//   }


//   Dabble.processInput();
  
//   float x = GamePad.getXaxisData();
//   servoPosition = map(x, -7, 7, 130, 10);
//   meuServo.write(servoPosition);

//   float y = GamePad.getYaxisData();
//   speed = map(y, -7, 7, -255, 255);
//   speed = abs(speed);


// if(menor > parar){
//   if(y < -1){
//   //move para tras
//   digitalWrite(MOTOR_A_IN1, LOW);
//   digitalWrite(MOTOR_A_IN2, HIGH);
//   analogWrite(PWM_PIN, speed);
//   }
//   if(y > 1){
//   //move para frente
//   digitalWrite(MOTOR_A_IN1, HIGH);
//   digitalWrite(MOTOR_A_IN2, LOW);
//   analogWrite(PWM_PIN, speed);
//   }
//   if(y > -1 && y < 1){
//   //para o motor
//     for (int i = speed; i >= 0; i) {
//       analogWrite(PWM_PIN, i);
//       i = i-300;
//       delay(5);
//     }
//   digitalWrite(MOTOR_A_IN1, LOW);
//   digitalWrite(MOTOR_A_IN2, LOW);
//   analogWrite(PWM_PIN, 0);
//   }
//   }
//   if(menor < parar){
//     if(y < -1){
//       //move para tras
//       digitalWrite(MOTOR_A_IN1, LOW);
//       digitalWrite(MOTOR_A_IN2, HIGH);
//       analogWrite(PWM_PIN, speed);
//     } else {
//      //para o motor
//       for (int i = speed; i >= 0; i) {
//         analogWrite(PWM_PIN, i);
//         i = i-300;
//         delay(5);
//       }
//       digitalWrite(MOTOR_A_IN1, LOW);
//       digitalWrite(MOTOR_A_IN2, LOW);
//       analogWrite(PWM_PIN, 0);
//     }
//   }
  
//   //Encoder
//   //Atualiza contador a cada segundo
//   if (millis() - timeold >= 100)
//   {
//     //Desabilita interrupcao durante o calculo
//     detachInterrupt(4);
//     rpm = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos;
//     velocidade = (0.376991118 * raio_metros * rpm);
//     timeold = millis();
//     pulsos = 0;

//     //Habilita interrupcao
//     attachInterrupt(4, contador, FALLING);

//      if(GamePad.isCirclePressed() == HIGH){
//         digitalWrite(buzzer, HIGH);
//      } else{
//         digitalWrite(buzzer, LOW);
//      }
//   }


//   //print no serial
//   // Serial.print("Distancia frente: ");
//   // Serial.println(menor);
//   // Serial.print("Distancia atras: ");
//   // Serial.println(distance4);

//   // Serial.println("Ultrassonicos: ");
//   // Serial.println(distance1);
//   // Serial.println(distance2);
//   // Serial.println(distance3);

//   // //distance 1 = esquerda
//   // //distance 2 = meio
//   // //distance 3 = direita
//   // //distance 4 = tras
//   // //menor = menor distancia dentre os ultrassonicos dianteiros

//   // Serial.print("RPM = ");
//   // Serial.println(rpm);
//   // Serial.print("Velocidade = ");
//   // Serial.print(velocidade);
//   // Serial.println(" Km/H");

//   // Serial.print("Bateria ESP = ");
//   // Serial.print(batesp);
//   // Serial.println("%");
//   // Serial.print("Bateria motor = ");
//   // Serial.print(batmotor);
//   // Serial.println("%");

//   // Serial.println();
//   // delay(500);

// } // endloop core 1