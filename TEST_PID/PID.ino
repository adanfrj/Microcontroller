#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int p,i,d, pid, u_pid, t_on, t_off;
float Kp = 10, Ki = 5, Kd = 20, y;
int error = 0, total_error = 0, d_error = 0, error_lama = 0, sp = 50;
int ts = 1000;
int ssr = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");                //This  string  is defined as a commmand for the Excel VBA to clear all the rows and columns
  Serial.println("LABEL,Waktu  ,Suhu  (C),  U  (%)");      //Perintah  Label  digunakan untuk membuat nama kolom pada baris pertama
  }
  
void loop() {
  sensors.requestTemperatures();
  y = sensors.getTempCByIndex(0);
  
  // hitung error
  error = sp -y;
  
  //Kontroller P
  p = Kp*error;

  //Kontroller I
  total_error = total_error + ts/2*(error_lama+error);
  i = Ki/1000*total_error;
  
  //saturasi sinyal I
  if (i > 100){
    i = 100;
  }
  else if (i < -100){
    i = -100;
  }
    
  // Kontroller D
  d_error = (error -error_lama)/ts;
  d = Kd*d_error;
  error_lama = error; 
  
  //Kontroller PID
  pid = p + i + d; 
  
  //Saturasi sinyal kontrol
  if (pid > 100) {
    pid = 100;
    }
  else if (pid < 0) {
    pid = 0;
    }
    
  //PWM arduino
  //u_pid = map(pid, 0, 100, 0, 255);
  //analogWrite(ssr,u_pid);
  //delay(1000);
  
act();
//kirim data
Serial.print("DATA,TIME,");
Serial.print(y);
Serial.print(",");
Serial.println(pid);
}     

void act(){
  //PWM manual
  t_on = pid*10; //t_on pwm
  t_off = 1000 -t_on; // t_off pwm
  if (pid == 100){
    analogWrite(ssr,255);
    delay(t_on); 
    }
    else if (pid <100){
      analogWrite(ssr,255);
      delay(t_on);
      analogWrite(ssr,0);
      delay(t_off); }
      
}
