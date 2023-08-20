int LDR = A0;
int LM35 = A1;
int nilaiLDR;
int nilaiLM35;
int button1=2;
int button2=3;
int nilaibutton1;
int nilaibutton2;
int LED_1 = 10;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(LDR, INPUT);
  pinMode(LM35, INPUT);
  Serial.begin(9600);
}

void loop() {
  nilaibutton1 = digitalRead(button1);
  nilaibutton2 = digitalRead(button2);
  
if (nilaibutton1 == HIGH)
  {
  digitalWrite(LDR, HIGH);
  nilaiLDR = analogRead(LDR);
  Serial.print("Nilai LDR = ");
  Serial.print(nilaiLDR);
  Serial.print(" LUX");
  Serial.println();
  }
  if (nilaiLDR >= 100)
  {
    digitalWrite(LED_1, HIGH);
  }
  else 
  {
    digitalWrite(LED_1, LOW);
  }
if (nilaibutton1 == LOW)
{
  digitalWrite(LDR, LOW);
}
  delay(1000);

if (nilaibutton2 == HIGH)
  {
  digitalWrite(LM35, HIGH);
  nilaiLM35=analogRead(LM35);
  nilaiLM35 = nilaiLM35 * 0.488;
  Serial.print("Nilai LM35 = ");
  Serial.print(nilaiLM35);
  Serial.print(" Celsius");
  Serial.println();
  if (nilaiLM35 >= 100)
  {
    digitalWrite(LED_1, HIGH);
  }
else if (nilaiLM35 <=100)
  {
  digitalWrite(LM35, LOW);
  }  

if (nilaibutton2==LOW)
  {
    digitalWrite(LM35, LOW);
  }
 delay(1000);
  }  
  }
  
