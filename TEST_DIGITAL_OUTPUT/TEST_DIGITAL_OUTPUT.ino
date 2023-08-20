// MUHAMMAD RAMADHAN
// TEST DIGITAL OUTPUT

const int led1 = 2; 
const int led2 = 3; 
const int led3 = 4;

void setup()
{
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  digitalWrite(led1,HIGH); 
  digitalWrite(led2,HIGH); 
  digitalWrite(led3,HIGH); 
}

void loop()
{
  digitalWrite(led1,LOW); 
  delay(1000); 
  digitalWrite(led2,LOW); 
  delay(1000); 
  digitalWrite(led3,LOW); 
  delay(1000); 
  digitalWrite(led3,HIGH); 
  delay(1000); 
  digitalWrite(led2,HIGH); 
  delay(1000); 
  digitalWrite(led1,HIGH); 
  delay(1000);
}
