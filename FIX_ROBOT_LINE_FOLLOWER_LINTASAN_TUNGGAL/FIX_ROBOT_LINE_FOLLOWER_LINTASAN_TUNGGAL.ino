//MUHAMMAD RAMADHAN
//FIX_ROBOT_LINE_FOLLOWER_LINTASAN_TUNGGAL
// Deteksi garis / benda hitam logika sensor = '0'
// Deteksi garis / benda putih logika sensor = '1'
// Sensor terpasang pada pin A0(kiri sudut), A1(kiri), A2(tengah), A3(kanan) dan A4(kanan sudut)
// Motor gearbox kiri terpasang pada pin D5 dan D6
// Motor gearbox kanan terpasang pada pin D9 dan D10

///// Pin sensor line follower
#define kiri_sudut A0
#define kiri A1
#define tengah A2
#define kanan A3
#define kanan_sudut A4

///// Pin motor gearbox
#define motor_kiri_P 5
#define motor_kiri_N 6
#define motor_kanan_P 9
#define motor_kanan_N 10

int in_kiri_sudut;
int in_kiri;
int in_tengah;
int in_kanan;
int in_kanan_sudut; 

int speed_base=80;
int speed_base_low=10;
int speed_low=20;
int speed_mid=80;
int speed_high=100;

int count=100;
int next=1; 
int ok=0;

void setup() {
  // put your setup code here, to run once:

pinMode(kiri_sudut,INPUT);
pinMode(kiri,INPUT);
pinMode(tengah,INPUT);
pinMode(kanan,INPUT);
pinMode(kanan_sudut,INPUT);
  
pinMode(motor_kiri_P,OUTPUT);
pinMode(motor_kiri_N,OUTPUT);
pinMode(motor_kanan_P,OUTPUT);
pinMode(motor_kanan_N,OUTPUT);
Serial.begin(9600);

// Robot line follower full sensor full putih ==> awal jalan maju lambat cari garis hitam
baca_sensor();
 if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1)  && (in_kanan==1) && (in_kanan_sudut==1))
  {
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base);//HIGH
  do
    {
    baca_sensor();
    if ((in_kiri_sudut==0) || (in_kiri==0) || (in_tengah==0)  || (in_kanan==0) || (in_kanan_sudut==0))
    {
    next=0; 
    }
    }
  while(next==1);
  next=1;
  }
}

void loop() {
  baca_sensor();
  ////////////// pergerakan robot //////////////////////////
  
  //////////////////////////////////////////////////////////
  // Robot line follower full sensor full hitam ==> berhenti
  if ((in_kiri_sudut==0) && (in_kiri==0) && (in_tengah==0) 
  && (in_kanan==0) && (in_kanan_sudut==0)){
  digitalWrite(motor_kiri_P,LOW);
  digitalWrite(motor_kiri_N,LOW);
  digitalWrite(motor_kanan_P,LOW);
  digitalWrite(motor_kanan_N,LOW);
  ok=0;
  }

  // langkah => 1 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kiri full speed (1 sensor)
  if ((in_kiri_sudut==0) && (in_kiri==1) && (in_tengah==1) 
  && (in_kanan==1) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,0);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_high);//HIGH
  ok=0;
  }

  // langkah => 2 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kiri (2 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1) 
  && (in_kanan==0) && (in_kanan_sudut==0)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,0);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_mid);//HIGH
  ok=0;
  }

  // langkah => 3 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kiri slow (1 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==0) && (in_tengah==1) 
  && (in_kanan==1) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base_low);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_low);//HIGH
  ok=0;
  }

  // langkah => 4 ///////////////////////////////////////////////////
  // Robot line follower bergerak => maju full speed (2 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==0) && (in_tengah==0) 
  && (in_kanan==1) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_mid);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_high);//HIGH
  ok=0;
  }

  // langkah => 5 ///////////////////////////////////////////////////
  // Robot line follower bergerak => maju full speed (1 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==0) 
  && (in_kanan==1) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_high);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_high);//HIGH
  ok=0;
  }

  // langkah => 6 /////////////////////////////////////////////////// 
  // Robot line follower bergerak => maju full speed (2 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==0) 
  && (in_kanan==0) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_high);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_mid);//HIGH
  ok=0;
  }

  // langkah => 7 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kanan slow (1 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1) 
  && (in_kanan==0) && (in_kanan_sudut==1)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_low);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base_low);//HIGH
  ok=0;
  }

  // langkah => 8 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kanan (2 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1) 
  && (in_kanan==0) && (in_kanan_sudut==0)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_mid);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,0);//HIGH
  ok=0;
  }
  // langkah => 9 ///////////////////////////////////////////////////
  // Robot line follower bergerak => belok kanan full speed (1 sensor)
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1) 
  && (in_kanan==1) && (in_kanan_sudut==0)){
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_high);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,0);//HIGH
  ok=0;
  }

  // langkah => 10 ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////
  // Robot line follower full sensor ==> cek sensor hilang garis hitam berapa kali sebelum berputar
  if ((in_kiri_sudut==1) && (in_kiri==1) && (in_tengah==1)  && (in_kanan==1) && (in_kanan_sudut==1))
  {
  //delay(1);
  ok++;
  if (ok>30)
  {
  do
  {
  ok=0;
  baca_sensor();
  analogWrite(motor_kiri_P,speed_base+speed_low);
  analogWrite(motor_kiri_N,0);//HIGH
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_low);
  Serial.println("putar");
  delay(1);
  if (in_tengah==0)
  {
  next=0; 
  analogWrite(motor_kiri_P,0);//LOW
  analogWrite(motor_kiri_N,speed_base+speed_base+speed_mid);
  analogWrite(motor_kanan_P,0);//LOW
  analogWrite(motor_kanan_N,speed_base+speed_base+speed_mid);
  delay(50);
  } 
  }
  while(next==1);
  next=1;
  }
  }
  ////////////////////////////////////////////////////////////////////////////////
  delay(5); 
}

void baca_sensor(){
  ///////// proses baca sensor
  in_kiri_sudut=digitalRead(kiri_sudut);
  in_kiri=digitalRead(kiri);
  in_tengah=digitalRead(tengah);
  in_kanan=digitalRead(kanan);
  in_kanan_sudut=digitalRead(kanan_sudut);   
}
