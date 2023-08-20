// MUHAMMAD RAMADHAN
// TEST ANALOG INPUT

int adc = 0; 
float volt = 0; 
 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  adc = analogRead(A5); 
  
  volt = (float) (0.004887585533*adc); 
  Serial.print("ADC = "); 
  Serial.print(adc); 
  Serial.print("\t Volt = "); 
  Serial.println(volt); 
  delay(500);   
}
