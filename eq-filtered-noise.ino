#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord1(in,0,myDsp,0);
AudioConnection patchCord2(myDsp,0,out,0);
AudioConnection patchCord3(myDsp,0,out,1);
//AudioConnection patchCord0(in,0,out,0);
//AudioConnection patchCord1(in,0,out,1);


void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.volume(0.5);
  myDsp.configurePeakEQFilter(5000, 800, 3.0);
}

void loop() {
  delay(100);
}
