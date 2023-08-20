// Program Konveyor pendeteksi logam dan Water Level
// Muhammad Ramadhan
// 40040319650081

const int sensorlogam = 2;
const int relaykonveyor = 9;
const int sensorproximity = 3;
const int valveair = 10;
int proximity = 0, logamdetek = 0;

void setup() 
  {
  pinMode (sensorlogam, INPUT);
  pinMode (sensorproximity, INPUT);
  pinMode (relaykonveyor, OUTPUT);
  pinMode (valveair, OUTPUT);
  }

void loop() {
  proximity = digitalRead(sensorproximity);
  logamdetek = digitalRead (sensorlogam);
  
  if ( logamdetek == HIGH && proximity == LOW ) // detektor logam mendeteksi
     { 
      digitalWrite (relaykonveyor, LOW); //konveyor berhenti
      digitalWrite (valveair, HIGH); //valve cairan menyala
      delay (1000);
     }
   
  if ( logamdetek == LOW && proximity == LOW ) // proximity mendeteksi penuh
     {
      digitalWrite (valveair, LOW); //valve cairan mati
      digitalWrite (relaykonveyor, HIGH); //konveyor berjalan
     }
     
  if (logamdetek == HIGH && proximity == HIGH ) // logam detektor dan proximity mendeteksi 1
     {
      digitalWrite (relaykonveyor, HIGH);
      digitalWrite (valveair, LOW);
      delay (1000);
     }
}
