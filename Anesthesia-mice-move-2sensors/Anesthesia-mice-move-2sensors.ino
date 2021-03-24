#include <DFRobot_AS7341.h>
#include <DFRobot_AS7341wire1.h>



DFRobot_AS7341 as7341;
DFRobot_AS7341wire1 as7341w1;

const int stepPin = 7; 
const int dirPin = 6; 
const int enable = 5;
const int buttonclock180 = 4;
const int buttoncounterclock180 = 3;
int microdelay=100;
// With the channel G I had a good response for the green UV ink.   

void setup() {
  // Sets the two pins as Outputs
  Serial.begin(115200);

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(buttonclock180,INPUT_PULLUP);
  pinMode(buttoncounterclock180,INPUT_PULLUP);
  
  digitalWrite(stepPin,LOW);
  digitalWrite(enable,HIGH);



  while (as7341.begin() != 0) {
    Serial.println("IIC init failed, please check if the wire connection is correct");
    delay(1000);
  }

  while (as7341w1.begin() != 0) {
    Serial.println("IIC init failed, please check if the wire connection is correct");
    delay(1000);
  } 

digitalWrite(enable,LOW);
}
void loop() {
  if (buttonclock180==LOW){
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making two full cycle rotation
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(microdelay); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(microdelay); 
  }
  }
  //digitalWrite(enable,HIGH);

  if (buttoncounterclock180==LOW){
  digitalWrite(dirPin,LOW); //Changes the rotations direction
   //Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(microdelay);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(microdelay);
  }
  }

  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;
  DFRobot_AS7341wire1::sModeOneData_t data3;
  DFRobot_AS7341wire1::sModeTwoData_t data4;

  //s1 Start spectrum measurement 
  //Channel mapping mode: 1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341.startMeasure(as7341.eF1F4ClearNIR);
  //Read the value of sensor data channel 0~5, under eF1F4ClearNIR
  data1 = as7341.readSpectralDataOne();
  
  Serial.print("s1F1(405-425nm):");
  Serial.println(data1.ADF1);
  Serial.print("s1F2(435-455nm):");
  Serial.println(data1.ADF2);
  Serial.print("s1F3(470-490nm):");
  Serial.println(data1.ADF3);
  Serial.print("s1F4(505-525nm):");   
  Serial.println(data1.ADF4);
  //Serial.print("Clear:");
  //Serial.println(data1.ADCLEAR);
  //Serial.print("NIR:");
  //Serial.println(data1.ADNIR);
  
  as7341.startMeasure(as7341.eF5F8ClearNIR);
  //Read the value of sensor data channel 0~5, under eF5F8ClearNIR
  data2 = as7341.readSpectralDataTwo();
  Serial.print("s1F5(545-565nm):");
  Serial.println(data2.ADF5);
  Serial.print("s1F6(580-600nm):");
  Serial.println(data2.ADF6);
  Serial.print("s1F7(620-640nm):");
  Serial.println(data2.ADF7);
  Serial.print("s1F8(670-690nm):");
  Serial.println(data2.ADF8);
  Serial.print("s1Clear:");
  Serial.println(data2.ADCLEAR);
  Serial.print("s1NIR:");
  Serial.println(data2.ADNIR);
  //delay(1000);

  //s2 Start spectrum measurement 
  //Channel mapping mode: 1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341w1.startMeasure(as7341w1.eF1F4ClearNIR);
  //Read the value of sensor data channel 0~5, under eF1F4ClearNIR
  data3 = as7341w1.readSpectralDataOne();
  
  Serial.print("s2F1(405-425nm):");
  Serial.println(data3.ADF1);
  Serial.print("s2F2(435-455nm):");
  Serial.println(data3.ADF2);
  Serial.print("s2F3(470-490nm):");
  Serial.println(data3.ADF3);
  Serial.print("s2F4(505-525nm):");   
  Serial.println(data3.ADF4);
  //Serial.print("Clear:");
  //Serial.println(data1.ADCLEAR);
  //Serial.print("NIR:");
  //Serial.println(data1.ADNIR);
  
  as7341w1.startMeasure(as7341w1.eF5F8ClearNIR);
  //Read the value of sensor data channel 0~5, under eF5F8ClearNIR
  data4 = as7341w1.readSpectralDataTwo();
  Serial.print("s2F5(545-565nm):");
  Serial.println(data4.ADF5);
  Serial.print("s2F6(580-600nm):");
  Serial.println(data4.ADF6);
  Serial.print("s2F7(620-640nm):");
  Serial.println(data4.ADF7);
  Serial.print("s2F8(670-690nm):");
  Serial.println(data4.ADF8);
  Serial.print("s2Clear:");
  Serial.println(data4.ADCLEAR);
  Serial.print("s2NIR:");
  Serial.println(data4.ADNIR);
  //delay(1000);
 
}
