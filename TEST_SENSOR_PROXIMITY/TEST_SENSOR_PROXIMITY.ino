// MUHAMMAD RAMADHAN
// TEST SENSOR PROXIMITY
// Sensor terpasang pada pin A0(kiri sudut), A1(kiri), A2(tengah), A3(kanan) dan A4(kanan sudut)

#define kiri_sudut A0
#define kiri A1
#define tengah A2
#define kanan A3
#define kanan_sudut A4

int in_kiri_sudut;
int in_kiri;
int in_tengah;
int in_kanan;
int in_kanan_sudut; 

void setup() {
  // put your setup code here, to run once:
pinMode(kiri_sudut,INPUT);
pinMode(kiri,INPUT);
pinMode(tengah,INPUT);
pinMode(kanan,INPUT);
pinMode(kanan_sudut,INPUT);


Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  in_kiri_sudut=digitalRead(kiri_sudut);
  in_kiri=digitalRead(kiri);
  in_tengah=digitalRead(tengah);
  in_kanan=digitalRead(kanan);
  in_kanan_sudut=digitalRead(kanan_sudut);

  Serial.print("logika sensor");
  Serial.print(" Kiri Sudut:");
  Serial.print(in_kiri_sudut);
  Serial.print(" ,Kiri:");
  Serial.print(in_kiri);
  Serial.print(" ,Tengah:");
  Serial.print(in_tengah);
  Serial.print(" ,Kanan:");
  Serial.print(in_kanan);
  Serial.print(" ,Kanan Sudut:");
  Serial.println(in_kanan_sudut);  
  delay(1000); 
}
