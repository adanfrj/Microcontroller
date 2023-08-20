//MUHAMMAD RAMADHAN
//TEST SENSOR DS18B20

#include <OneWire.h>
#include <DallasTemperature.h>
// Kabel data terhubung dengan pin 2
int ONE_WIRE_BUS=2;
// Setting oneWire untuk siap berkomunikasi
OneWire oneWire(ONE_WIRE_BUS);
// melewatkan referensi oneWire untuk terhubung dengan
DallasTemperature sensors(&oneWire);
void setup(void)
{
 // memulai komunikasi serial dengan komputer melalui
 Serial.begin(9600);
 // memulai sensor
 sensors.begin();
}
void loop(void){

 sensors.requestTemperatures(); 
 Serial.print("Celsius temperature: ");
 Serial.print(sensors.getTempCByIndex(0));
 Serial.print(" - Fahrenheit temperature: ");
 Serial.println(sensors.getTempFByIndex(0));
 delay(1000);
}
