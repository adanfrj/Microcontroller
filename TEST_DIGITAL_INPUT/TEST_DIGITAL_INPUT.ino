// MUHAMMAD RAMADHAN
// TEST DIGITAL INPUT

const int btna = 2; 
const int btnb = 3; 
const int btnc = 4; 
 
int btnstatea = 0; 
int btnstateb = 0; 
int btnstatec = 0; 
 
int counta = 0; 
int countb = 0; 
int countc = 0;

void setup()
{ 
  pinMode(btna,INPUT); 
  pinMode(btnb,INPUT); 
  pinMode(btnc,INPUT);
  Serial.begin(9600);
}

void loop()
{
  btnstatea = digitalRead(btna); 
  btnstateb = digitalRead(btnb); 
  btnstatec = digitalRead(btnc);
  
  if(btnstatea == LOW) { 
    counta++; 
    Serial.print("A="); 
    Serial.print(counta); 
    Serial.print("  B="); 
    Serial.print(countb); 
    Serial.print("  C="); 
    Serial.println(countc); 
    delay(300); 
  } 
  
  else if(btnstateb == LOW) { 
    countb++; 
    Serial.print("A="); 
    Serial.print(counta); 
    Serial.print("  B="); 
    Serial.print(countb); 
    Serial.print("  C="); 
    Serial.println(countc); 
    delay(300); 
  } 
  
  else if(btnstatec == LOW) { 
    countc++; 
    Serial.print("A="); 
    Serial.print(counta); 
    Serial.print("  B="); 
    Serial.print(countb); 
    Serial.print("  C="); 
    Serial.println(countc); 
    delay(300); 
  }
}
