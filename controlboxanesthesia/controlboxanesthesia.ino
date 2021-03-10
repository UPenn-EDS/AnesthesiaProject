// Please use old bootloader
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DFRobot_I2CMultiplexer.h"
DFRobot_I2CMultiplexer I2CMulti(0x70);

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define BC 2
#define BB 4
#define BD 3
#define BA 5
#define LEDgreen 6
#define LEDyellow 7
#define PUL 10
#define Dir 9
#define ENA 8

int ButtonACstate=LOW;
unsigned long starttime=0;
unsigned long SessionLengthMinutes = 2;
unsigned long SessionLengthHours = 0;
unsigned long SessionLengthInMiliseconds = 0;

void setup() {
  
Serial.begin(9600);

pinMode(BA, INPUT_PULLUP); // button A
pinMode(BB, INPUT_PULLUP); // button B
pinMode(BC, INPUT_PULLUP); // button C
pinMode(BD, INPUT_PULLUP); // button D
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
I2CMulti.selectPort(0);
display.clearDisplay();



//    display.clearDisplay();
//    display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.print("Valve Open");
//  display.setCursor(25,50);
//  display.print("4");
//  display.println("%");
//  display.display();

  //delay(2000);
  

}

void loop() {

 //I2CMulti.selectPort(0);

 
 
 if (digitalRead(BA)==LOW){
    Serial.println("A");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("A");
    display.display();
  
 }

 if (digitalRead(BB)==LOW){
    Serial.println("B");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("B");
    display.display();
  
 }

 if (digitalRead(BC)==LOW){
    Serial.println("C");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("C");
    display.display();
  
 }

 if (digitalRead(BD)==LOW){
    Serial.println("D");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("D");
    display.display();
  
 }
    

}
