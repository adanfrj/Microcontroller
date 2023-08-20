//MUHAMMAD RAMADHAN
//TEST NODEMCU - BLYNK

#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

//============================================
//AUTH WIFI
const char *ssid = "aminah siswoyo"; //SSID WIFI
const char *pass = "aduhlupa"; //PASS WIFI
char auth[] = "EJu-kkumukXVWlgjjrW7AZPAkDs32chk"; // Token dari blynk APP
WiFiClient client;
//============================================

SoftwareSerial mySerial(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  Blynk.begin(auth, ssid, pass, "prakitblog.com",8181);
  WiFi.begin(ssid, pass);
  {
    delay(1000);
    mySerial.print(".");
  }
  mySerial.println("");
  mySerial.println("Wifi Connected");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
