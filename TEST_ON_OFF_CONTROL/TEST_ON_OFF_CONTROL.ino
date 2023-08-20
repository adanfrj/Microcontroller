#include <OneWire.h>
//MUHAMMAD RAMADHAN
//TEST ON OFF CONTROL WITH HEATER

#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int t_act = 530, t_actgon = 15 ,t_actgoff = 285;
int ssr = 3; // alamati pin SSR
int kondisi = 0;
  
void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");                //This  string  is defined as a commmand for the Excel VBA to clear all the rows and columns
  Serial.println("LABEL,Waktu ,Suhu (C)");   //Perintah Label digunakan untuk membuat nama kolom pada baris pertama
  
  }
  void loop() {
   
  switch (kondisi){
      case 0 : // kondisi inisialisasi
    for(int i=0; i<t_act; i++){
    sensors.requestTemperatures();
    Serial.print("DATA,TIME,");
    Serial.println(sensors.getTempCByIndex(0));    
    analogWrite(ssr, 255);
    delay(1000);
    }
    kondisi = 1;

    case 1 : // kondisi siklus OFF
    for(int i=0; i<t_actgoff; i++){
    sensors.requestTemperatures();
    Serial.print("DATA,TIME,");
    Serial.println(sensors.getTempCByIndex(0));    
    analogWrite(ssr, 0);
    delay(1000);
    }
    kondisi = 2;

    case 2 : // kondisi siklus ON
    for(int i=0; i<t_actgon; i++){
    sensors.requestTemperatures();
    Serial.print("DATA,TIME,");
    Serial.println(sensors.getTempCByIndex(0));    
    analogWrite(ssr, 255);
    delay(1000);
    };
    kondisi = 1;
  }
 }     
      




  
