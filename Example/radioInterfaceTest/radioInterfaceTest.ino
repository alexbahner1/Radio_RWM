/*
 * this a test for thr radio interface 
 * this test it makes sure the button the vol pot work in the system
*/

// all Libs here
#include <Si4703_Breakout.h> // radio lib
#include <Wire.h> // I2C lib 

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

}


void displayInfo()
{
   Serial.print("Channel:"); Serial.print(cha); 
   Serial.print(" Volume:"); Serial.println(vol); 
}

void setPotVolume(){
   int potval = analogRead(pot);
   
   int volNew = (potval *1000) / (1023* 1000)  * 15; 
   Serial.println(volNew);
//   if (volNew != vol){
//    vol = volNew; 
//    radio.setVolume(vol);
//    displayInfo();
//   } 
  }

void buttonSeek(){
  
  } 


  
