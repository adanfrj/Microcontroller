// MUHAMMAD RAMADHAN
// TEST ANALOG OUTPUT

const int led = 9; 
int adc = 0; 

void setup()
{
  pinMode(led,OUTPUT); 
}

void loop()
{
  adc = analogRead(A5); 
  adc = map(adc, 0, 1023, 0, 255); 
  analogWrite(led, adc);
}
