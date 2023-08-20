//MUHAMMAD RAMADHAN
//TEST SENSOR MAX6675 AND DS18B20

#include "max6675.h" //INCLUDE THE LIBRARY
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int thermoDO = 9;
int thermoCS = 8;
int thermoCLK = 13;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
 Serial.begin(9600);
 Serial.println("MAX6675 test");
 sensors.begin();
 Serial.println("CLEARDATA"); //This string is defined as a commmand for the Excel VBA to clear all the rows and columns
 Serial.println("LABEL,Waktu ,DS18B20(C),Termokopel Tipe K (C)"); //Perintah Label digunakan untuk membuat nama kolom pada baris pertama
 // wait for MAX chip to stabilize
 delay(500);
}

void loop() {
 // basic readout test, just print the current temp
 sensors.requestTemperatures();
 Serial.print("DATA,TIME,");
 Serial.print(sensors.getTempCByIndex(0));
 Serial.print(",");
 Serial.println(thermocouple.readCelsius());

 delay(3000);
}
