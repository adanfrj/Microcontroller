//MUHAMMAD RAMADHAN FIRJATULLAH
//40040319650081
//TUGAS AKHIR

#include <Wire.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//=================auth WIFI Connect=======================================
const char *ssid = "adan"; //SSID WIFI
const char *pass = "adan141220"; //PASS WIFI
char auth[] = "nF5BgSS9pR41zJwdNQNf8enG4n3y1Jk4"; // Token dari blynk APP
WiFiClient client;


//=================Pin yang dipakai========================

int pinIR1 = D1; //IR Sensor 1
int pinIR2 = D2; //IR Sensor 2

//====================Variabel=============================

int jmlTotalTelurBesar = 0;
int jmlTotalTelurKecil = 0;
int jmlTelurTotal = 0;

boolean stateIR1 = true;
boolean stateIR2 = true;


//======================Setup===============================
 
void setup() 
{
  //==============mulai serial==============================
  Serial.begin(115200); //BUKA SERIAL NODEMCU - P

  //====Mode fungsi untuk setiap variabel / pin============
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);

//==========================Inisialisasi Sistem============================
  Blynk.begin(auth, ssid, pass, "blynk.cloud",80);
  WiFi.begin(ssid, pass);
  {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  delay(2000);
}

//==============================END SETUP=================================



//==============================LOOP======================================
 
void loop() 
{ 
  Blynk.run();
  SystemStart();
}

//===============================END LOOP=================================




void SystemStart()
{  

//===================Perhitungan Jumlah Telur====================================
  //Jumlah Telur Kecil
  Blynk.virtualWrite(V0, jmlTotalTelurKecil);
  delay(100);
  
  //Jumlah Telur Besar
  Blynk.virtualWrite(V1, jmlTotalTelurBesar);
  delay(100);


  //jika mendeteksi telur ke wadah kecil maka +1
  if (!digitalRead (pinIR1) && stateIR1) 
  {
    jmlTotalTelurKecil++;
    stateIR1 = false;
    delay(100); 
  }
  if(digitalRead(pinIR1))
  {
    stateIR1 = true;
    delay(100);
  }
  Serial.print("Jumlah Telur Kecil: ");
  Serial.print(jmlTotalTelurKecil);
  Serial.println(" Buah");
  Serial.println();

  //jika mendeteksi telur ke wadah besar maka +1
  if (!digitalRead (pinIR2) && stateIR2) 
  {
    jmlTotalTelurBesar++;
    stateIR2 = false;
    delay(100);
  }
  if(digitalRead(pinIR2))
  {
    stateIR2 = true;
    delay(100);
  }

  Serial.print("Jumlah Telur Besar: ");
  Serial.print(jmlTotalTelurBesar);
  Serial.println(" Buah");
  Serial.println();
  
  
  //Total Jumlah Telur
    jmlTelurTotal = jmlTotalTelurBesar + jmlTotalTelurKecil;
    Blynk.virtualWrite(V2, jmlTelurTotal);
    delay(100); 

    Serial.print("Jumlah Total Telur: ");
    Serial.print(jmlTelurTotal);
    Serial.println(" Buah");
    Serial.println();
}
