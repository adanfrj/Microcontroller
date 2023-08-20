//MUHAMMAD RAMADHAN
//KONTROL TEMPERATURE DENGAN SETPOINT

#include <Keypad.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//inisialisasi keypad
char customKey, mulaiKey; //char stringAngka[2];
int indexKeypad = 0;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};

//inisialisasi variabel
int keypd= 0;
int ssr = 3; // alamati pin SSR
float sp;
float diff, temp_now;
float T_cutoff, T_cuton, nilaicd, nilaisp, nilaidiff;
int a = -100, b = -50, c = 0, d = 5, a1 = 0, b1 = 5, c1 = 10, a2 = 5, b2 = 15, c2 = 29, a3 = 22, b3 = 30, c3 = 50, d3 = 55;
int u1 = 0, u2 = 200, u3 = 500, u4 = 1000;
float ua, ub, u, mf1, mf2, mf3, mf4,x, r1, r2, r3, r4, error;

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup()
{
  Serial.begin(9600);
  Serial.println("CLEARDATA");  
  Serial.println("LABEL,Waktu  ,Suhu  (C),Error,heat on(u)");
  Serial.println (u1);
  Serial.println (u2);
  Serial.println (u3);
  Serial.println (u4);
  lcd.begin();
  lcd.backlight();
  pinMode(ssr, OUTPUT);
  
  sp = 0;
  diff = 0;
  nilaisp = sp;
  nilaidiff = diff;
  T_cutoff = sp + (diff / 2);
  T_cuton = sp - (diff / 2);
  delay(50);
  lcd.clear();
}

void loop()
{
  customKey = customKeypad.getKey();

  if (keypd == 0) {
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1.SET ON-OFF");
  }

  if (keypd == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("2.MULAI");
  }

  if (keypd == 2) {
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("3.CEK ON-OFF");
  }

  switch (customKey)
  {
    case '0' ... '9':
      break;

    case '#':
      break;
    case '*':
      break;
    case 'A':
      keypd++;
      break;

    case 'B':
      keypd--;
      break;

    case 'C':
      break;

    case 'D':
      if (keypd == 0) {
        lcd.clear();
        //analogWrite(ssr,0);
        setsp();
        setdiff();
      }

      if (keypd == 1) {
        lcd.clear();
        mulai();
      }

      if (keypd == 2) {
        lcd.clear();
        //analogWrite(ssr,0);
        cekonoff();
      }
      break;
  }

  if (keypd > 2) {
    keypd = 0;
  }

  if (keypd < 0) {
    keypd = 2;
  }
}

void setdiff() {
  lcd.setCursor(0, 0);
  lcd.print("SET DIFF ");
  customKey = customKeypad.getKey();

  if (customKey >= '0' && customKey <= '9')
  {
    diff = diff * 10 + (customKey - '0');
    lcd.setCursor(0, 1);
    lcd.print(diff);
    T_cutoff = sp + (diff / 2);
    T_cuton = sp - (diff / 2);
  }

  if (customKey == '*') {
    lcd.clear();
    delay(1000);
    nilaidiff = diff;
    return;
  }

  setdiff();
}

void setsp() {
  lcd.setCursor(0, 0);
  lcd.print("SET SP ");
  customKey = customKeypad.getKey();

  if (customKey >= '0' && customKey <= '9')
  {
    sp = sp * 10 + (customKey - '0');
    lcd.setCursor(0, 1);
    lcd.print(sp);
    //lcd.print(customKey);
    //sp = customKey;
  }

  if (customKey == '*') {
    lcd.clear();
    delay(1000);
    nilaisp = sp;
    return;
  }

  setsp();
}

void cekonoff() {
  lcd.setCursor(0, 0);
  lcd.print("SP = ");
  lcd.print(nilaisp);

  lcd.setCursor(0, 1);
  lcd.print("Control diff = ");
  lcd.print(nilaidiff);


  customKey = customKeypad.getKey();

  if (customKey == '*') {
    lcd.clear();
    delay(1000);
    return;
  }
  cekonoff();
}

void mulai() {
  if (sp == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Mohon Set SP");
    lcd.setCursor(0, 1);
    lcd.print("dan Diff Dahulu");
    delay(2000);
    return;
  }

  sensors.requestTemperatures();
  x = sp - temp_now;
  temp_now = sensors.getTempCByIndex(0);

  mf1=max(min(min((x-a)/(b-a),(d-x)/(d-c)),1),0);
  mf2=max(min((x-a1)/(b1-a1),(c1-x)/(c1-b1)),0);
  mf3=max(min((x-a2)/(b2-a2),(c2-x)/(c2-b2)),0);
  mf4=max(min(min((x-a3)/(b3-a3),(d3-x)/(d3-c3)),1),0);
  r1=mf1*u1;
  r2=mf2*u2;
  r3=mf3*u3;
  r4=mf4*u4;
  u =(r1+r2+r3+r4)/(mf1+mf2+mf3+mf4);
  
  Serial.println();
  Serial.print ("membership function 1 : ");
  Serial.println (mf1);
  Serial.print ("membership function 2 : ");
  Serial.println (mf2);
  Serial.print ("membership function 3 : ");
  Serial.println (mf3);
  Serial.print ("membership function 4 : ");
  Serial.println (mf4);


  if (u > 0) {
    analogWrite(ssr, 255);
    analogWrite(ssr, 0);
    lcd.setCursor(13, 1);
    delay(u);
    delay(100);
  }

  else {
    analogWrite(ssr, 0);
    delay (100);
  }
  

  Serial.print("L1");
  Serial.println(temp_now);
  lcd.setCursor(0, 0);
  lcd.print("SP=");
  lcd.print(sp);
  lcd.print(" Y=");
  lcd.print(temp_now);
  lcd.setCursor(9, 1);
  lcd.print("X=");
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("U=");
  lcd.print(u);
  lcd.print(" ");
  
  delay(200); customKey = customKeypad.getKey();
  if (customKey == '*') {
    lcd.clear();
    analogWrite(ssr, 0);
    resetFunc(); //call reset
    delay(800);
    return;
  }
  mulai();
}
