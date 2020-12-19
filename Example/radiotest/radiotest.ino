#include <Si4703_Breakout.h>
#include <Wire.h>

int resetPin = 2;
int SDIO = A4;
int SCLK = A5;

Si4703_Breakout radio(resetPin, SDIO, SCLK);
int channel = 908;
int volume = 14;
char rdsBuffer[10];

void setup() {
  // put your setup code here, to run once:
  radio.powerOn();
  radio.setVolume(0);
  radio.setChannel(channel);
  radio.setVolume(volume);
}

void loop() {
  // put your main code here, to run repeatedly:
//   radio.setChannel(channel);
//  radio.setVolume(volume);

}
