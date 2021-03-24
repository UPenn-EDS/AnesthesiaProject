#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;

const int stepPin = 7; 
const int dirPin = 6; 
const int enable = 5;
const int LEDR = 9; // This actually a yellow LED
const int LEDG = 8; // This is Green LED in the system
const int Button = 2;
int microdelay=100;
unsigned long timedelay=3000;
unsigned long timedelaystatus=0;
float valueink=35.00; // Initial value? Irrelevant, please fix. 

// With the channel G I had a good response for the green UV ink.   

void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600);
  Serial.println("AS7265x Spectral Triad Example");

  if(sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while(sensor.begin() == false);
    Serial.println("Sensor Ready");
  }
  
  Serial.println("A,B,C,D,E,F,G,H,I,J,K,L,R,S,T,U,V,W");


  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(Button,INPUT_PULLUP);
  digitalWrite(stepPin,LOW);
  digitalWrite(enable,HIGH);
  digitalWrite(LEDR,HIGH);
  digitalWrite(LEDG,HIGH);
  while(digitalRead(Button)==HIGH){  //Loop to set the value of the ink in the mice. Please take the mice and place it inside the tube, below the sensor. hold the mice there and press the A button until the RED LED go off. 
  sensor.takeMeasurementsWithBulb();
  valueink=sensor.getCalibratedG()-5.00; // Generate a table of values and define 5 as a #define
  Serial.println(valueink);
  }
  digitalWrite(LEDR,LOW);   // Yellow LED goes OFF meaning, sensor is calibrated with the ready.  
  delay(1000);
  while(digitalRead(Button)==HIGH){ // After placing the mice and closing the chamber press the A button to start session. 
  digitalWrite(LEDG,HIGH);
  delay(100);
  digitalWrite(LEDG,LOW);
  delay(100);
  }
  delay(2000);
  digitalWrite(LEDG,HIGH);  // The experiment has begun
}
void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making two full cycle rotation
 digitalWrite(enable,LOW);
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(microdelay); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(microdelay); 
  }
  digitalWrite(enable,HIGH);
  
 timedelaystatus=millis();
 while((millis()-timedelaystatus)<timedelay){  // Every 3 seconds take a reading
  sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured
  //Serial.println(sensor.getCalibratedG());
    while(sensor.getCalibratedG() < valueink){ // take multiple measurements and make sure is less than the calibrated value
      sensor.takeMeasurementsWithBulb();
      Serial.println(sensor.getCalibratedG());
      Serial.println("Mice ready");
      digitalWrite(LEDR,HIGH);     // If the LED yellow is ON the mouse is asleep
  }
  digitalWrite(LEDR,LOW);          // The mouse woke up with the tatoo up there
 }
  digitalWrite(enable,LOW);
  digitalWrite(dirPin,LOW); //Changes the rotations direction
   //Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(microdelay);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(microdelay);
  }
  digitalWrite(enable,HIGH);
  
 timedelaystatus=millis();
 while((millis()-timedelaystatus)<timedelay){
  sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured
  while(sensor.getCalibratedG() < valueink){
  sensor.takeMeasurementsWithBulb();
  Serial.println(sensor.getCalibratedG());
  Serial.println("Mice ready");
  digitalWrite(LEDR,HIGH);
  }
  digitalWrite(LEDR,LOW);
 }
 
}
