//MUHAMMAD RAMADHAN
//POMPA AIR OTOMATIS DENGAN HCSR04

int trigpin=6;
int echopin=5;
int relay=7;
long echotime;
float distance;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(trigpin, LOW);
}

void loop() {
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  echotime=pulseIn(echopin, HIGH);
  distance = 0.0001 * ((float)echotime*340.0)/2.0;

  if (distance <= 5) digitalWrite(relay, HIGH);
  if (distance > 9 && distance <= 12) digitalWrite(relay, LOW);
  
  delay(100);

}
