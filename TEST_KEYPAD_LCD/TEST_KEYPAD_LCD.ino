//MUHAMMAD RAMADHAN
//TEST_KEYPAD_WITH_LCD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
 {'1', '2', '3', 'A'},
 {'4', '5', '6', 'B'},
 {'7', '8', '9', 'C'},
 {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
lcd.begin();
lcd.backlight();
Serial.begin(9600);
}

void loop() {
 char customKey = customKeypad.getKey();
 lcd.setCursor(0, 0);
 if (customKey){
 lcd.clear();
 lcd.print(customKey);
 }

}
