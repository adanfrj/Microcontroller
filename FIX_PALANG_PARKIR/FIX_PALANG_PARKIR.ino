//MUHAMMAD RAMADHAN
//PALANG PARKIR DENGAN TOMBOL

#include <Servo.h>
Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}
void loop()
{
  int tombolBuka = digitalRead(3);
  int tombolTutup = digitalRead(5);
  
  if (tombolBuka == 0)
  {
    myservo.write(180);
    Serial.println("TUTUP TOMBOL");
    delay(1000);
  }
  if (tombolTutup == 0)
  {
    myservo.write(77);
    Serial.println("BUKA TOMBOL");
    delay(1000);
  }
}
