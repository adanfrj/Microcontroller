//MUHAMMAD RAMADHAN
//PEMANAS / HEATER PROJECT

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int ssr = 3; // alamati pin SSR
int sp = 40;
float diff = 2, temp_now;
float T_cutoff, T_cutin;  

void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");                //This  string  is defined as a commmand for the Excel VBA to clear all the rows and columns
  Serial.println("LABEL,Waktu  ,Suhu  (C)");      //Perintah  Label  digunakan  untuk membuat nama kolom pada baris pertama
  }

void loop() {
  sensors.requestTemperatures();
  T_cutoff = sp + (diff/2);
  T_cutin = sp -(diff/2);
  temp_now = sensors.getTempCByIndex(0);
  
  if (temp_now >= T_cutoff) 
  {
    analogWrite(ssr,0);
  }
  
  else if (temp_now <=T_cutin) 
  {
    analogWrite(ssr,255);
  }
  Serial.print("DATA,TIME,");
  Serial.println(temp_now);
  delay(1000);
  
}
