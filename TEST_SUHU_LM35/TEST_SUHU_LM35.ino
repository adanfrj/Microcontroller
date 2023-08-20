//MUHAMMAD RAMADHAN
//TEST SUHU LM35

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
int x=1;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(3, LOW);
  digitalWrite(13, LOW);
  digitalWrite(A0, LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("MONITOR SUHU");
  lcd.setCursor(0, 1);
  lcd.print("SUHU : ");    
  delay(10);

}

void loop() {
  Serial.begin(9600);
  x=digitalRead(3);
  int lm35 = analogRead(A0);
  float vin = (lm35/1024.0)*5000;
  int suhu = vin/10;
  Serial.available();
  if (Serial.available()>0)
  (x=Serial.read());
 
  if (x==1)
  {
    digitalWrite(13, HIGH);
  }

  else 
  {
    digitalWrite(13, LOW);
  }
  
  
  if ( suhu < 40 ) 
  {
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  else if ( suhu > 40 and suhu < 70 )
  {
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
  }

  else
  {
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH); 
    digitalWrite(13, LOW);
  }

  lcd.setCursor(9, 1);
  lcd.print((int)(suhu));
  lcd.print(" C");
  Serial.print(suhu);
  Serial.print('C');
  
  Serial.println(" ");
  delay(1000);

}
