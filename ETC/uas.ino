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

char customKey, mulaiKey;
//char stringAngka[2];
int indexKeypad = 0;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'}, 
{'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {11,10,9,8};
byte colPins[COLS] = {7,6,5,4};

int x = 0;
int ssr = 3; // alamati pin SSR
float sp;
float diff, temp_now;
float T_cutoff, T_cuton, nilaicd, nilaisp, nilaidiff;
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void(* resetFunc) (void) = 0; //declare reset function @ address 0 

void setup()
{
Serial.begin(9600); 
lcd.begin(); 
lcd.backlight(); 
pinMode(ssr,OUTPUT); 
sp = 0;
diff = 0; 
nilaisp = sp; 
nilaidiff = diff;
T_cutoff = sp + (diff/2); 
T_cuton = sp - (diff/2);
delay(50);
lcd.clear();
}


void loop()
{
customKey = customKeypad.getKey();

if(x == 0){
//lcd.clear(); 
lcd.setCursor(0,0); 
lcd.print("1.SET ON-OFF");
}

if(x == 1){ lcd.clear(); 
lcd.setCursor(0,0); 
lcd.print("2.MULAI");
}

if(x == 2){
//lcd.clear();
lcd.setCursor(0,0);
lcd.print("3.CEK ON-OFF");
} 
switch(customKey)
{
case '0' ... '9':
break;

case '#':
break;

case '*':
break;

case 'A': 
x++; 
break;

case 'B': 
x--; 
break;

case 'C':
break;

case 'D': 
if(x == 0){ 
lcd.clear();
//analogWrite(ssr,0);
setsp();
setdiff();

}
if(x == 1){
lcd.clear();
mulai();
}
if(x == 2){
lcd.clear();
//analogWrite(ssr,0);
cekonoff();
}
break;
}

if(x > 2){
x = 0;
}

if(x < 0){
x = 2;
}

} 
void setdiff(){ 
lcd.setCursor(0,0); 
lcd.print("SET DIFF   ");

customKey = customKeypad.getKey();

if(customKey >= '0' && customKey <= '9')
{
diff = diff * 10 + (customKey - '0');
lcd.setCursor(0,1);
lcd.print(diff);
T_cutoff = sp + (diff/2); T_cuton = sp - (diff/2);

}

if(customKey == '*'){ 
lcd.clear(); 
delay(1000);
nilaidiff = diff;
return;
}

setdiff();
}

void setsp(){ 
lcd.setCursor(0,0); 
lcd.print("SET SP    ");

customKey = customKeypad.getKey();

if(customKey >= '0' && customKey <= '9')
{
sp = sp * 10 + (customKey - '0');
lcd.setCursor(0,1);
lcd.print(sp);
//lcd.print(customKey);
//sp = customKey;

}

if(customKey == '*'){ 
lcd.clear(); 
delay(1000);
nilaisp = sp;
return;
}

setsp();
}

void cekonoff(){ 
lcd.setCursor(0,0); 
lcd.print("SP = "); 
lcd.print(nilaisp);


lcd.setCursor(0,1); 
lcd.print("Control diff = "); 
lcd.print(nilaidiff);


customKey = customKeypad.getKey();

if(customKey == '*'){ 
lcd.clear(); 
delay(1000);
return;
}

cekonoff();
}

void mulai(){ 
if (sp==0) { 
lcd.setCursor(0, 0);
lcd.print("Mohon Set SP"); 
lcd.setCursor(0, 1); 
lcd.print("dan Diff Dahulu"); 
delay(2000);
return;
}

sensors.requestTemperatures(); 
T_cutoff = sp + (diff/2);
T_cuton = sp - (diff/2);
temp_now = sensors.getTempCByIndex(0);
if (temp_now >= T_cutoff) {
analogWrite(ssr,0);
}
else if (temp_now <= T_cuton) {
analogWrite(ssr,255);
}
//Serial.print("DATA,TIME,"); 
Serial.print("L1"); 
Serial.println(temp_now); 
lcd.setCursor(0, 0); 
lcd.print("SP= ");
lcd.print(sp); 
lcd.print("      "); 
lcd.setCursor(0, 1); 
lcd.print("Y "); 
lcd.print(temp_now); 
lcd.print("      "); 
delay(200); 

customKey = customKeypad.getKey();
if(customKey == '*'){ 
lcd.clear(); 
analogWrite(ssr,0); 
resetFunc(); //call reset 
delay(800);
return;
}

mulai();
}
