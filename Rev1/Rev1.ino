/*
 * this a test for thr radio interface 
 * this test it makes sure the button the vol pot work in the system
*/

// all Libs here
#include <Si4703_Breakout.h> // radio lib
#include <Wire.h> // I2C lib 
#include "U8glib.h"

//Radio var 
int resetPin = 2;
int SDIO = A4;
int SCLK = A5;
Si4703_Breakout radio(resetPin, SDIO, SCLK);
int cha = 908;
int vol = 13;

//Interface vars 
int pot = A0;
int seekup = 12; //button 1
int seekdown = A1; //button 2
int push1 = 0;
int push2 = 0; 

int stat1 = A2;
int push3 = 1;
int buttonStat;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;
long whenButton = 0;
long whenButtonReleased = 0;


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
  pinMode(seekup, INPUT_PULLUP);
  pinMode(seekdown, INPUT_PULLUP);
  pinMode(stat1, INPUT_PULLUP);
}

void loop() {
  setPotVolume();
  //buttonSeek();
  int B1state = digitalRead(seekup);
  int B2state = digitalRead(seekdown);
  if(B1state == HIGH && push1 == 0){
    push1 = 1; 
    cha = radio.seekUp();
    displayInfo();  
  }
  if(B1state == LOW){push1 = 0;}
  //
  if(B2state == HIGH && push2 == 0){
    push2 = 1; 
    cha = radio.seekDown();
    displayInfo();  
  }
  if(B2state == LOW){push2 = 0;} 


  int val = digitalRead(stat1);
//  if(val == LOW && push3 == 0){
//    push3 = 1; 
//    cha = radio.seekDown();
//    displayInfo();  
//  }
//  if(val == HIGH){push3 = 0;}
  long now = millis();
  if ((digitalRead(stat1) == LOW && (now-whenButton) > 200) && whenButton < whenButtonReleased)
  {
   whenButton = now;
   cha = radio.seekDown();
  }
  if (digitalRead(stat1) == HIGH && (now-whenButtonReleased) > 200)
  {
   whenButtonReleased = now;
  }
  
  if (val != lastButtonState) {
    lastDebounceTime = millis();
//    Serial.println("hit");
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (val!= buttonStat) {
      buttonStat = val;

      if (buttonStat == HIGH) {
//        Serial.println("SAVED");
      }
    }
  }
  lastButtonState = val;
  
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

void setPotVolume(){
   int potval = analogRead(pot);
   
   int volNew = (float)potval / 1023  * 15; 
//   int ans = (float)val / 1023 * 15;
//   Serial.println(volNew);
   if (volNew != vol){
    vol = volNew; 
    radio.setVolume(vol);
    displayInfo();
   } 
  }

void buttonsave(){
//  int reading = digitalRead(buttonPin);
//   if (reading != lastButtonState) {
//    lastDebounceTime = millis();
//  }
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    // whatever the reading is at, it's been there for longer than the debounce
//    // delay, so take it as the actual current state:
//
//    // if the button state has changed:
//    if (reading != buttonState) {
//      buttonState = reading;
//
//      // only toggle the LED if the new button state is HIGH
//      if (buttonState == HIGH) {
//        ledState = !ledState;
//      }
//    }
//  }
  
  }
void draw() {
 
  u8g.setFont(u8g_font_profont11);  // select font
  //u8g.drawStr(0, 15, "Nokia 5110..");  // put string of display at position X, Y
  //u8g.drawStr(29, 35, "HELLO!!!!");
  u8g.setPrintPos(0,15);
  u8g.print("FM:");
  u8g.print(cha);
}
