void setPotVolume(){
   int potval = analogRead(pot);
   
   int volNew = (float)potval / 1023  * 15; 
   if (volNew != vol){
    vol = volNew; 
    radio.setVolume(vol);
    displayInfo();
   } 
  }

void seekButtons(){ 
  skUpB.loop();
  if(skUpB.isPressed()){
    cha = radio.seekUp();
    displayInfo();
  }
  skDownB.loop();
  if(skDownB.isPressed()){
    cha = radio.seekDown();
    displayInfo();
  }
}

void saveStation(){
  stat1B.loop();
  if(stat1B.isPressed()){
    lastPressed = millis(); 
    s1Bstate = 1;
    Serial.println(cha);
    }
  if(s1Bstate == 1 && (millis() - lastPressed) > pressDelay){
//    cha = radio.seekDown();
    EEPROM.put(0,cha);
    s1Bstate = 0;
    }
  if(stat1B.isReleased()){
//    cha = radio.seekUp();
    EEPROM.get(0,cha);
    radio.setChannel(cha);
    Serial.println(cha);
    s1Bstate = 0;
    displayInfo();
  }
 
  }

void draw() {
 
  u8g.setFont(u8g_font_profont11);  // select font
  //u8g.drawStr(0, 15, "Nokia 5110..");  // put string of display at position X, Y
  //u8g.drawStr(29, 35, "HELLO!!!!");
  u8g.setPrintPos(0,15);
  u8g.print("FM:");
  int pcha = cha/10;
  int scha = cha%10;
  u8g.print(pcha);
  u8g.print(".");
  u8g.print(scha);
  
  
}
