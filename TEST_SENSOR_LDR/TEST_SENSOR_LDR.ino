//MUHAMMAD RAMADHAN
//TEST SENSOR LDR

int LDR = A2;
int LED_1 = 13;
int LED_2 = 12;
int LED_3 = 11;
int nilaiLDR = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_1, OUTPUT);
  Serial.begin (9600) ;
  pinMode(LED_2, OUTPUT);
  Serial.begin (9600) ;
  pinMode(LED_3, OUTPUT);
  Serial.begin (9600) ;
}

void loop() 
{
  // put your main code here, to run repeatedly:
  nilaiLDR = analogRead (LDR) ;
  Serial.print ("Nilai LDR = ") ;
  Serial.println (nilaiLDR);

  if (nilaiLDR < 6)
  {
    digitalWrite (LED_1, HIGH) ;
    delay(500);
    digitalWrite (LED_2, HIGH);
    delay(1000);
    digitalWrite (LED_3, HIGH);
    delay(1500);
  }
  else
  {
    digitalWrite (LED_1, LOW) ;
    delay(500);
    digitalWrite (LED_2, LOW) ;
    delay(1000);
    digitalWrite (LED_3, LOW) ;
    delay(1500);
  }
}
