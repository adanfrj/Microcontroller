//MUHAMMAD RAMADHAN
//TEST SENSOR HCSR04

int trigPin = 2;
int echoPin = 3;
int buzzerPin = 7;
int ledPin=5;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(trigPin, OUTPUT );
pinMode(echoPin, INPUT );
pinMode(buzzerPin, OUTPUT);
pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
long duration, distance;
digitalWrite(trigPin, HIGH);
digitalWrite(trigPin, LOW);
digitalWrite(ledPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration * 0.034) /2;

if (distance >=25)
{
  digitalWrite(trigPin,LOW);
  digitalWrite(buzzerPin,LOW);
  digitalWrite(ledPin, LOW);
}
if (distance <=15)
{
  digitalWrite(trigPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
  digitalWrite(ledPin, HIGH);
  delay(500);

  digitalWrite(trigPin,LOW);
  digitalWrite(buzzerPin,LOW);
  digitalWrite(ledPin, LOW);
  delay(500);
 
}
if (distance <=10)
{
  digitalWrite(trigPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
  digitalWrite(ledPin, HIGH);
  delay(100);

  digitalWrite(trigPin,LOW);
  digitalWrite(buzzerPin,LOW);
  digitalWrite(ledPin, LOW);
  delay(100);
}

}
