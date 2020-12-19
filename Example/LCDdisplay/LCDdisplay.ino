
#include "U8glib.h"
//#define backlight 11
// SPI Com: ClK = 13, DIN = 11, CE = 10, DC = 9, Reset = 8

// SPI for radio CLK = 7, DN = 11, CE = 10, DC = 9, RST = 8

U8GLIB_PCD8544 u8g(7, 11, 10, 9, 8);

void setup() {
  // put your setup code here, to run once:
  u8g.setFont(u8g_font_10x20); // Sets fonts
  u8g.setPrintPos(2, 15);
 
}

void loop() {  
  u8g.firstPage();
  do {  
    draw();
  } while( u8g.nextPage() );
  delay(1000);   
}
  
void draw() {
 
  u8g.setFont(u8g_font_profont11);  // select font
  u8g.drawStr(0, 15, "Nokia 5110..");  // put string of display at position X, Y
  u8g.drawStr(29, 35, "HELLO!!!!");
  
  
}
