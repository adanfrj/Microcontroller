//MUHAMMAD RAMADHAN
//TEST DOORLOCK WITH KEYPAD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Password.h>
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = { 4, 5, 6, 7 }; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { A0, A1, A2, A3 }; // Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 16, 2);
Password password = Password("458900"); //Ganti Password yang kalian inginkan

const int buzzer = 2;
const int relay = 8;

int alarm = 0;
uint8_t alarmStat = 0;
uint8_t maxError = 5;
uint8_t pwMode = 0;
uint8_t pwPos = 0;
bool access = false;

void setup() {
  Serial.begin(9600);
  lcd.begin();

  keypad.addEventListener(keypadEvent); //add an event listener for this keypad

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  tone (buzzer, 1200);
  lcd.setCursor (0, 0);
  lcd.print(F("Keypad Doorlock"));
  lcd.setCursor (3, 1);
  lcd.print(F("Loading"));
  for (int i = 0; i < 3; i++) {
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  noTone (buzzer);
  delay(50);
}

void loop() {
  keypad.getKey();

  if (alarm >= maxError) {
    alarmStat = 1;
  }

  if (alarmStat == 0 && pwMode == 0) {
    lcd.setCursor (0, 0);
    lcd.print(F(" -System Ready- "));
    lcd.setCursor (0, 1);
    lcd.print(F(" Enter Password "));
  }

  if (alarmStat == 1) {
    lcd.setCursor (0, 0);
    lcd.print(F("-System LOCKED- "));
    lcd.setCursor (0, 1);
    lcd.print(F(" Please Wait "));
    for (int i = 60; i > 0; i--) {
      tone (buzzer, 1800);
      lcd.setCursor (13, 1); lcd.print(i);
      lcd.print(F("  ")); delay (1000);
    }
    noTone (buzzer);
    alarmStat = 0;
    alarm = 0;
  }
}

void keypadEvent(KeypadEvent eKey) {
  switch (keypad.getState()) {
    case PRESSED:
      Serial.print("Pressed: ");
      Serial.println(eKey);

      pwMode = 1;
      pwPos = pwPos + 1;
      if (pwPos == 1) {
        lcd.clear();
      }
      lcd.setCursor (0, 0);
      lcd.print(F("Password Entered"));
      if (pwPos < 7) {
        lcd.setCursor (4 + pwPos, 1);
        lcd.print(F("*"));
      }

      switch (eKey) {
        case '*': checkPassword(); break;
        case '#': password.reset();
          pwPos = 0;
          lcd.clear();
          delay(200);
          lcd.setCursor (0, 0);
          lcd.print(F("Password Entered"));
          break;

        default: password.append(eKey);
      }
  }
}

void checkPassword() {
  if (password.evaluate()) {
    Serial.println("Password OK");
    lcd.setCursor (0, 1);
    lcd.print(F("   -diterima-   "));
    alarm = 0;
    diterima();
    password.reset();
    pwPos = 0;
  }

  else {
    Serial.println("Password SALAH");
    lcd.setCursor (0, 1);
    lcd.print(F("   -ditolak-   "));
    alarm = alarm + 1;
    ditolak();
    password.reset();
    pwPos = 0;
  }
}

void diterima() {
  digitalWrite(relay, LOW);
  tone (buzzer, 900);
  delay(100);
  tone (buzzer, 1200);
  delay(100);
  tone (buzzer, 1800);
  delay(200);
  noTone(buzzer);
  delay(600);
  lcd.setCursor (0, 0);
  lcd.print(F(" Silahkan Masuk "));
  lcd.setCursor (0, 1);
  lcd.print(F("AutoLock after "));
  for (int i = 5; i > 0; i--) {
    lcd.setCursor (15, 1); lcd.print(i);
    delay (1000);
  }

  digitalWrite(relay, HIGH);
  pwMode = 0;
  lcd.clear();
  delay(50);
}

void ditolak() {
  tone (buzzer, 900);
  delay(200);
  noTone(buzzer);
  delay(200);
  tone (buzzer, 900);
  delay(200);
  noTone (buzzer);
  delay(500);
  pwMode = 0;
  lcd.clear();
  delay(50);
}
