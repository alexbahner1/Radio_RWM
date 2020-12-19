/*
 * this a test for thr radio interface 
 * this test it makes sure the button the vol pot work in the system
*/

// all Libs here
#include <Si4703_Breakout.h> // radio lib
#include <Wire.h> // I2C lib 
#include "U8glib.h"
#include <ezButton.h>
#include <EEPROM.h>

//Radio var 
int resetPin = 2;
int SDIO = A4;
int SCLK = A5;
Si4703_Breakout radio(resetPin, SDIO, SCLK);
unsigned int cha = 908;
int vol = 13;

//Interface vars 
int pot = A0;
//int seekup = 12; //button 1
//int seekdown = A1; //button 2
//int stat1 = A2;
ezButton skUpB(12); // seek up button for radio
ezButton skDownB(A1); // seek down button for radio
ezButton stat1B(A2);
unsigned long lastPressed = 0;
unsigned long pressDelay = 3000;
int s1Bstate = 0; 



U8GLIB_PCD8544 u8g(7, 11, 10, 9, 8);

void setup() {
  //serial steup
  Serial.begin(9600);
  Serial.println("Interface test begin:");
  
  // radio setup
  radio.powerOn();
  
  radio.setChannel(cha);
  radio.setVolume(vol);

  // interface setup
  pinMode(pot,OUTPUT);
}

void loop() {
  setPotVolume();
  seekButtons();
  saveStation();

  
 
  
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );

}


void displayInfo()
{
   Serial.print("Channel:"); Serial.print(cha); 
   Serial.print(" Volume:"); Serial.println(vol); 
}
