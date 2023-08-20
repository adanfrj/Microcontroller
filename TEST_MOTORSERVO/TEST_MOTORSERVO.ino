#include <Servo.h> //library servo

Servo myservo; // membuat variabel servo untuk dikendalikan
int pos = 0; // deklarasi variabel untuk posisi sudut

void setup()

{

 myservo.attach(9); //deklarasi servo pada pin 9

}

void loop()

{

  myservo.write(0);
  delay(2000);
  myservo.write(15);
  delay(2000);
  myservo.write(30);
  delay(2000);
  myservo.write(45);
  delay(2000);
  myservo.write(60);
  delay(2000);
  myservo.write(75);
  delay(2000);
  myservo.write(90);
  delay(2000);
  myservo.write(105);
  delay(2000);
  myservo.write(120);
  delay(2000);
  myservo.write(135);
  delay(2000);
  myservo.write(150);
  delay(2000);
  myservo.write(165);
  delay(2000);
  myservo.write(180);
  delay(2000);
}
