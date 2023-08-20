//MUHAMMAD RAMADHAN
//TEST PENAMPIL DATA ADC

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
int val = 0;
void setup(){
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Arduino ADC LCD");
  lcd.setCursor(0, 1);
  lcd.print("Data ADC: ");    
  delay(10);}
  
void loop(){
  val = analogRead(A0);
  lcd.setCursor(9, 1);
  lcd.print(val);
  lcd.print(" dec");
  delay(100);
}
