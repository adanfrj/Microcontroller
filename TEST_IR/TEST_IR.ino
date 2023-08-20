//MUHAMMAD RAMADHAN
//TEST INFRARED SENSOR

#define pinIR 9 
 
void setup() {
   Serial.begin(115200);
   pinMode(pinIR, INPUT); //Declare pin D5 as input
   Serial.println("IR Detection");
   delay(3000);
}
 
void loop() {
   int datasensor = digitalRead(pinIR); //instructions for monitoring digital values
   Serial.print("Sensor Value: ");
   Serial.println(datasensor);
   if (datasensor == LOW) { //instruction to activate the LED when an object is detected
     Serial.println("Object Detected");
     delay(3000);
   }
 
   else {
     Serial.println("No Object"); //instruction to activate the LED when an object is detected
     delay(3000);
   }
}
