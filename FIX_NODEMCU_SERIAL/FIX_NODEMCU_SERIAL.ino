//MUHAMMAD RAMADHAN FIRJATULLAH
//TEST CONNECTION NODEMCU-ARDUINO
//40040319650081
//TUGAS AKHIR

#include <Wire.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

//================= Variabel Data Serial ===================================
//pin D6 RX D7 TX
SoftwareSerial DataSerial(12,13); //penerima data serial (sensor) dari arduino
String arrayData[3];
int jmlTotalTelurKecil, jmlTotalTelurBesar, jmlTelurTotal;

//millis pengganti delay untuk menghindari nodemcu reset
unsigned long previousMillis = 0; //waktu terakhir pengecekan
const long interval = 1000;       //berapa lama waktu pengecekan
//================= Auth WIFI Connect =======================================
const char *ssid = "adan"; //SSID WIFI
const char *pass = "adan141220"; //PASS WIFI
char auth[] = "nF5BgSS9pR41zJwdNQNf8enG4n3y1Jk4"; // Token dari blynk APP
WiFiClient client;
//===========================================================================

void setup() 
{
//============== Mulai serial ==============================
  Serial.begin(9600); //BUKA SERIAL NODEMCU - PC
  DataSerial.begin(9600);
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
  MembacaData();
}

//===============================END LOOP=================================

void MembacaData()
{  
  //Konfigurasi millis
  unsigned long currentMillis = millis(); //baca waktu saat ini
  if (currentMillis - previousMillis >= interval) // waktu saat ini - waktu sebelumnya lebih dari 1 detik (waktunya membaca kembali)
  {
    //update previousmillis
    previousMillis = currentMillis;

    //prioritaskan untuk pembacaan data dari Arduino (hasil kiriman data)
    //baca data serial
    String data = "";
    while(DataSerial.available()>0)
    {
      data += char(DataSerial.read());
    }

    //buang spasi data
    data.trim();

    //Jika isi variabel data tidak kosong maka tampilkan pada aplikasi
    if (data != "")
    {
      //Format data = SensorIR1#SensorIR2#JumlahTotalIR1&IR2
      //Pecah data
      int index = 0; //pengurut data, data ke 0 adalah sensor IR1, data ke 1 adalah IR2
      for(int i=0; i<=data.length(); i++) //pembacaan dari karakter ke 0 (pertama)
      {
        char pemisah = '#'; // apabila terbaca #
        if (data[i] != pemisah) //jika bertemu dengan #, maka masukkan arraydata[0]
          arrayData[index] += data[i];
        else
          index++; //variabel index +1
      }

      //pastikan data yang dikirim lengkap , urutan 0=IR1, 1=IR2, 2=TotalTelur
      if (index == 2)
      {
        //tampilkan nilai sensor ke serial monitor
        Serial.println("Jumlah Telur Kecil : " + arrayData[0]); //nilai sensor IR1
        Serial.println("Jumlah Telur Besar : " + arrayData[1]); //nilai sensor IR2
        Serial.println("Jumlah Total Telur : " + arrayData[2]); //jumlah total telur
        Serial.println();
      }
      //Isi variabel yang akan dikirim
      jmlTotalTelurKecil = arrayData[0].toInt();
      jmlTotalTelurBesar = arrayData[1].toInt();
      jmlTelurTotal = arrayData[2].toInt();

      Blynk.virtualWrite(V0, jmlTotalTelurKecil);
      Blynk.virtualWrite(V1, jmlTotalTelurBesar);
      Blynk.virtualWrite(V2, jmlTelurTotal);
      
      arrayData[0] = "";
      arrayData[1] = "";
      arrayData[2] = "";
    }
    
    //minta data ke arduino 
    DataSerial.println("Yes");
  }
}
