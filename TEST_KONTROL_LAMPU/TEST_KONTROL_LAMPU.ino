//MUHAMMAD RAMADHAN
//TEST KONTROL LAMPU WITH RTC

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231 rtc(SDA, SCL);
Time waktu;

int relay = 8;
int buzz = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  rtc.begin();
  rtc.setTime(9, 59, 40);
  rtc.setDate(07, 11, 2022);
  rtc.setDOW(4);

  lcd.begin();
  lcd.backlight();

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  pinMode(buzz, OUTPUT);
  

}

void nyalaLED(){
  digitalWrite(relay, HIGH);
}

void matiLED(){
  digitalWrite(relay, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(0,0);
  lcd.print("Tgl : ");
  lcd.setCursor(6,0);
  lcd.print(rtc.getDateStr()); //mengambil data tgl

  lcd.setCursor(0, 1);
  lcd.print("Jam : ");
  lcd.setCursor(6, 1);
  lcd.print(rtc.getTimeStr()); //mengambil jam
  delay(1000);

  waktu = rtc.getTime();

  Serial.println(waktu.hour);
  Serial.println(waktu.min);


  //cycle 1
  if (waktu.hour >= 10 && waktu.min >= 0) {
    matiLED();
    Serial.println("MATI");
  }
  
  if (waktu.hour >= 10 && waktu.min >= 1){
    nyalaLED();
    Serial.println("NYALA");
  }
  

  //cycle 2
  if (waktu.hour >= 10 && waktu.min >= 2){
    matiLED();
    Serial.println("MATI");
  }
 
  if (waktu.hour >= 10 && waktu.min >= 3){
    nyalaLED();
    Serial.println("NYALA");
  }

  //cycle 3
  if (waktu.hour >= 10 && waktu.min >= 4){
    matiLED();
    Serial.println("MATI");
  }
 
  if (waktu.hour >= 10 && waktu.min >= 5){
    nyalaLED();
    Serial.println("NYALA");
  }

  

  


}
