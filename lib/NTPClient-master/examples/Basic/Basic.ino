#include <CST816S.h>

#include <ESP_Panel_Board_Internal.h>
#include <ESP_Panel_Conf_Internal.h>
#include <ESP_Panel_Library.h>
#include <ESP_Panel.h>
#include <ESP_PanelLog.h>
#include <ESP_PanelTypes.h>
#include <ESP_PanelVersions.h>

#include <CST816S.h>

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
