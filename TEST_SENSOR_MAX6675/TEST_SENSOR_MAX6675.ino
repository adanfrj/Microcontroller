//MUHAMMAD RAMADHAN
//TEST SENSOR MAX6675

#include "max6675.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16, 2);

int thermoDO = 9;
int thermoCS = 8;
int thermoCLK = 13;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
Serial.begin(9600);
Serial.println("Sensor MAX6675 Test");
delay(500);

lcd.begin();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Muhammad Ramadhan");
lcd.setCursor(0, 1);
lcd.print("Sensor MAX6675");
}

void loop() {
Serial.print("C = ");
Serial.println(thermocouple.readCelsius());
Serial.print("F = ");
Serial.println(thermocouple.readFahrenheit());
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temperature");

lcd.setCursor(0,1);// set cursor at character 0, line 1
lcd.print(thermocouple.readCelsius()); 
lcd.setCursor(5,1);// set cursor at character 9, line 1
lcd.print(" "); 
lcd.setCursor(6,1);// set cursor at character 9, line 1
lcd.print("C");    
lcd.setCursor(7,1);// set cursor at character 9, line 1
lcd.print(" ");       
lcd.setCursor(8,1);// set cursor at character 9, line 1
lcd.print(thermocouple.readFahrenheit()); // print temperature in ahrenheit
lcd.setCursor(13,1);// set cursor at character 9, line 1      
lcd.print(""); 
lcd.setCursor(14,1);// set cursor at character 9, line 1
lcd.print("F"); 
delay(1000);
}
