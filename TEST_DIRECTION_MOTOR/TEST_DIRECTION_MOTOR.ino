// MUHAMMAD RAMADHAN
// TEST DIRECTION MOTOR

#define motor_kiri_P 5
#define motor_kiri_N 6
#define motor_kanan_P 9
#define motor_kanan_N 10

void setup() {
  // put your setup code here, to run once:
pinMode(motor_kiri_P,OUTPUT);
pinMode(motor_kiri_N,OUTPUT);
pinMode(motor_kanan_P,OUTPUT);
pinMode(motor_kanan_N,OUTPUT);
Serial.begin(9600);
Serial.println("Cek pergerakan arah dan putaran motor robot     ");
Serial.println("================================================");
delay(5000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Motor kiri bergerak => maju
  digitalWrite(motor_kiri_P,LOW);
  digitalWrite(motor_kiri_N,HIGH);
  Serial.println("Motor kiri bergerak => Maju");
  Serial.println();
  delay(5000); 
  
  // Motor kiri bergerak => mundur
  digitalWrite(motor_kiri_P,HIGH);
  digitalWrite(motor_kiri_N,LOW);
  Serial.println("Motor kiri bergerak => Mundur");
  Serial.println();
  delay(5000); 

  // Motor kiri berhenti berputar
  digitalWrite(motor_kiri_P,LOW);
  digitalWrite(motor_kiri_N,LOW);
  Serial.println("Motor kiri berhenti berputar");
  Serial.println();
  delay(5000); 

  // Motor kanan bergerak => maju
  digitalWrite(motor_kanan_P,LOW);
  digitalWrite(motor_kanan_N,HIGH);
  Serial.println("Motor kiri bergerak => Maju");
  Serial.println();
  delay(5000); 
  
  // Motor kanan bergerak => mundur
  digitalWrite(motor_kanan_P,HIGH);
  digitalWrite(motor_kanan_N,LOW);
  Serial.println("Motor kiri bergerak => Mundur");
  Serial.println();
  delay(5000); 

  // Motor kanan berhenti berputar
  digitalWrite(motor_kanan_P,LOW);
  digitalWrite(motor_kanan_N,LOW);
  Serial.println("Motor kanan berhenti berputar");
  Serial.println();
  delay(5000); 

  // Robot line follower bergerak => maju
  digitalWrite(motor_kiri_P,LOW);
  digitalWrite(motor_kiri_N,HIGH);
  digitalWrite(motor_kanan_P,LOW);
  digitalWrite(motor_kanan_N,HIGH);
  Serial.println("Robot line follower bergerak => maju");
  Serial.println();
  delay(5000); 

  // Robot line follower bergerak => mundur
  digitalWrite(motor_kiri_P,HIGH);
  digitalWrite(motor_kiri_N,LOW);
  digitalWrite(motor_kanan_P,HIGH);
  digitalWrite(motor_kanan_N,LOW);
  Serial.println("Robot line follower bergerak => mundur");
  Serial.println();
  delay(5000); 


  // Robot line follower berhenti bergerak
  digitalWrite(motor_kiri_P,LOW);
  digitalWrite(motor_kiri_N,LOW);
  digitalWrite(motor_kanan_P,LOW);
  digitalWrite(motor_kanan_N,LOW);
  Serial.println("Robot line follower berhenti bergerak");
  Serial.println();
  delay(5000); 

}
