//MUHAMMAD RAMADHAN FIRJATULLAH
//TEST CONNECTION NODEMCU-FIREBASE
//TUGAS AKHIR

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//================= Konfig Firebase =====================================
#define FIREBASE_HOST "realtime-iot-3ccc3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "WmN3ThsmKw1hJyua0scIKg66HBwfZPvpFRmiOWj2"

//=================== Konfig WIFI =======================================
#define WIFI_SSID "adan" //SSID WIFI
#define WIFI_PASSWORD "adan141220" //PASS WIFI

//=================Pin yang dipakai========================

#define pinIR1 D1 //IR Sensor 1
#define pinIR2 D2 //IR Sensor 2

//====================Variabel=============================

int jmlTotalTelurBesar;
int jmlTotalTelurKecil;
int jmlTelurTotal;

boolean stateIR1 = true;
boolean stateIR2 = true;


//======================Setup===============================
 
void setup() 
{
  //==============mulai serial==============================
  Serial.begin(115200); //BUKA SERIAL NODEMCU - PC 

  //====Mode fungsi untuk setiap variabel / pin============
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);

//==========================Inisialisasi Sistem============================
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan...");

  //apabila tidak terkoneksi
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  //apabila terkoneksi
  Serial.println();
  Serial.print("Terhubung dengan WIFI");
  Serial.print(WiFi.localIP());

  //Koneksi Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

//==============================END SETUP=================================



//==============================LOOP======================================
 
void loop() 
{ 
  SystemStart();
}

//===============================END LOOP=================================




void SystemStart()
{  

//===================Perhitungan Jumlah Telur====================================
  //Kirim ke firebase
  Firebase.setInt("data/sensorIR1", jmlTotalTelurKecil);
  Firebase.setInt("data/sensorIR2", jmlTotalTelurBesar);
  Firebase.setInt("data/jmltelur", jmlTelurTotal);
  delay(10);


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
    delay(100); 
    Serial.print("Jumlah Total Telur: ");
    Serial.print(jmlTelurTotal);
    Serial.println(" Buah");
    Serial.println();
}
