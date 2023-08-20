//MUHAMMAD RAMADHAN
//TEST VOLTMETER

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
int adc1=0;
float tegangan = 0;
int tegangan2=0;

void setup() {
 Serial.begin(9600);
 pinMode(A2, INPUT);
 pinMode(A0, OUTPUT); 
 pinMode(A4, OUTPUT);
 digitalWrite(A0,LOW);
 digitalWrite(A4,HIGH);
 lcd.begin(16, 2);
 lcd.setCursor(0, 0);
 lcd.print("Volt Meter Delphi");
 lcd.setCursor(0, 1);
 lcd.print("VOLT = ");
 delay(10);

}

void loop() {
adc1 = analogRead(2);
tegangan = (float)(adc1*0.004887585532);
tegangan2=tegangan*1000;
Serial.print(tegangan2);
Serial.println("A");
lcd.setCursor(3, 1);
lcd.print(tegangan,2);
lcd.print(" volt ");
delay(1000);
}
