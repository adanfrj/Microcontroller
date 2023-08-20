//MUHAMMAD RAMADHAN FIRJATULLAH
//40040319650081
//TUGAS AKHIR

#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define DOUT A3
#define CLK A2

Servo myservo1, myservo2, myservo3;
LiquidCrystal_I2C lcd(0x27, 16, 2);

//================= Pin yang dipakai ========================
HX711 scale(DOUT, CLK);
int pinIR1 = 2; //IR Sensor 1
int pinIR2 = 3; //IR Sensor 2
int pinIR3 = 4; //IR Sensor 3
int pinMotorConveyor = 5; //Motor Conveyor  
int resetButton = 12; // Button Reset

//==================== Variabel =============================
int weight; //berat telur
int calibration_factor = 378; // Faktor kalibrasi loadcell
int jmlTelurBesar = 0;
int jmlTotalTelurBesar = 0;
int jmlTelurKecil = 0;
int jmlTotalTelurKecil = 0;
int jmlTelurTotal = 0;
int deteksiTangan = 0;
int posmotor = 0;
boolean stateIR1 = true;
boolean stateIR2 = true;
boolean stateIR3 = true;

unsigned long previousMillisOn = 0; 
unsigned long previousMillisOff = 0; 
const long intervalOn = 15000; 
const long intervalOff = 15000; 

//==========================================================


//====================== Setup ===============================
void setup() 
{
  //============== Mulai serial ==============================
  Serial.begin(9600);
  
  //=======deklarasi pin motor servo========================
  myservo1.attach(8); //SEPARATOR TELUR KECIL
  myservo2.attach(9); //SEPARATOR TELUR BESAR
  myservo3.attach(10); //PENDORONG TELUR DI LOADCELL
  myservo1.write(180);
  myservo2.write(170);
  myservo3.write(180);

  //==== Mode fungsi untuk setiap variabel / pin ============
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
  pinMode(pinIR3, INPUT);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(pinMotorConveyor, OUTPUT);

  //==== Kondisi awal motor conveyor ========================
  digitalWrite(pinMotorConveyor, HIGH);


//===================== Inisialisasi Perhitungan Loacell ====================

  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  
//========================== Inisialisasi Sistem ============================
  lcd.begin();
  lcd.setCursor(2,1);
  lcd.print("SORTIR TELUR");
  lcd.setCursor(3,0);
  lcd.print("MONITORING");
  delay(3000);
  lcd.clear();  
}
//============================== END SETUP =================================








//============================== LOOP ======================================
 
void loop() 
{ 
  InitLoadcell();
  PerhitunganBeratTelur();
  PerhitunganJumlahTelur();
  ConveyorBerhentidanBerjalan();
  resetLoadCell();
  
}

//=============================== END LOOP =================================







//======================== KUMPULAN FUNGSI SISTEM ==========================
void InitLoadcell()
{
  //Memulai Perhitungan
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  weight = scale.get_units(5);
}


void PerhitunganBeratTelur()
{
  unsigned long currentMillisOn = millis();
  unsigned long currentMillisOff = millis();
  
  //Berat Telur
    lcd.setCursor(0, 1);
    lcd.print("Berat: ");
    lcd.setCursor(7, 1);
    lcd.print(weight);
    lcd.print(" gr                    ");
    delay(1);

    Serial.print("Berat: ");
    Serial.print(weight);
    Serial.println(" gr");
    Serial.println();
    
    //jika terdeteksi berat telur kecil, maka motor separator telur kecil akan bergerak sehingga telur dapat masuk ke dalam kemasan telur kecil


    if (currentMillisOff - previousMillisOff >= intervalOff) 
    {
      if (weight <= 0 )
      {
        myservo1.write(180);
        myservo2.write(175);
        myservo3.write(180);
      }
      previousMillisOff = currentMillisOff;
    }
    

    if (currentMillisOn - previousMillisOn >= intervalOn) 
    {
      if (weight >= 20 && weight <=50) 
      {
        myservo1.write(130);

        for (posmotor=180; posmotor>=120; posmotor-=1)
        {
          myservo3.write(posmotor);
          delay(10);
        }
      } 
     

      //jika terdeteksi berat telur besar, maka motor separator telur besar akan bergerak sehingga telur dapat masuk ke dalam kemasan telur besar
      if (weight > 50 )
      {
        myservo2.write(125);

        for (posmotor=180; posmotor>=120; posmotor-=1)
        {
          myservo3.write(posmotor);
          delay(10);
        }
      }
      
      previousMillisOn = currentMillisOn;
    }

   
}


void PerhitunganJumlahTelur()
{
  //=================== Perhitungan Jumlah Telur ====================================
  //Jumlah Telur Kecil
  lcd.setCursor(0, 0);
  lcd.print("K: ");
  lcd.setCursor(2  , 0);
  lcd.print(jmlTotalTelurKecil);
  delay(1);

  //jika mendeteksi telur ke wadah kecil maka +1
  if (!digitalRead (pinIR1) && stateIR1) 
  {
    jmlTelurKecil++;
    jmlTotalTelurKecil++;
    stateIR1 = false;
    Serial.println(jmlTelurKecil);
    delay(1); 
  }
  if(digitalRead(pinIR1))
  {
    stateIR1 = true;
    delay(1);
  }

  //Jumlah Telur Besar
  lcd.setCursor(6, 0);
  lcd.print("B: ");
  lcd.setCursor(8, 0);
  lcd.print(jmlTotalTelurBesar);
  delay(1);

  //jika mendeteksi telur ke wadah kecil maka +1
  if (!digitalRead (pinIR2) && stateIR2) 
  {
    jmlTelurBesar++;
    jmlTotalTelurBesar++;
    stateIR2 = false;
    Serial.println(jmlTelurBesar);
    delay(1);
  }
  if(digitalRead(pinIR2))
  {
    stateIR2 = true;
    delay(1);
  }
  
  //Total Jumlah Telur
    jmlTelurTotal = jmlTotalTelurBesar + jmlTotalTelurKecil;
    lcd.setCursor(12, 0);
    lcd.print("T: ");
    lcd.setCursor(14, 0);
    lcd.print(jmlTelurTotal);
    Serial.println(jmlTelurTotal);
    delay(1); 
}


void ConveyorBerhentidanBerjalan()
{
  if (!digitalRead (pinIR3) && stateIR3) 
  {
    deteksiTangan = 1;
    stateIR3 = false;
    delay(1); 
  }
  if(digitalRead(pinIR3))
  {
    deteksiTangan = 0;
    stateIR3 = true;
    delay(1);
  }

  //============================= Cycle Konveyor Berhenti =====================================

  //Jika jumlah telur besar / kecil mencapai +5, maka motor konveyor mati
  
  //================================ Cycle berhenti 1 ========================================
  if (jmlTelurBesar == 5)
  {
     digitalWrite(pinMotorConveyor, LOW);
     jmlTelurBesar = 0;    
  }
  if (jmlTelurKecil == 5)
  {
     digitalWrite(pinMotorConveyor, LOW);
     jmlTelurKecil = 0;
  }
  //==================================== End Cycle 1 =====================================
  



//============================= Cycle Konveyor Berjalan =====================================

  //jika sensor IR 3 telur di loadcell mendeteksi adanya tangan maka konveyor on

  //====================================== Cycle 1 =======================================
  
  if (deteksiTangan == 1) //jika sensor IR 3 mendeteksi tangan maka konveyor on
  {
    digitalWrite(pinMotorConveyor, HIGH);
  }

  //==================================== End Cycle 1 =====================================

}

void resetLoadCell()
{
  if ( digitalRead(resetButton) == LOW)
  {
    scale.set_scale();
    scale.tare(); //Reset the scale to 0
  }
}

//=============================== END KUMPULAN FUNGSI SISTEM =============================
