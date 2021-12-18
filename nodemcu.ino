#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

SoftwareSerial mySerial (D1, D2);

/* Add your SSID and password below. */
const char* ssid = "";
const char* password = "";

WiFiClient  client;

/* Add your Thingspeak channel number and write API key below. */
unsigned long myChannelNumber = 0;
const char * myWriteAPIKey = "";

unsigned long lastTime = 0;
unsigned long timerDelay = 1;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
  if ((millis() - lastTime) > timerDelay)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Connecting...");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("Connected.");
    }

    String msg = mySerial.readStringUntil('\r');
    msg.toFloat();
    Serial.println(msg);
    msg = msg.toFloat();

    int x = ThingSpeak.writeField(myChannelNumber, 1, msg, myWriteAPIKey);

    if (x == 200) {
      Serial.println("Channel Update Successful.");
    }
    else {
      Serial.println("Channel Update Unsuccessful. HTTP Error Code: " + String(x));
    }
    
    lastTime = millis();
  }
}
