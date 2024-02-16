#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioOutputI2S out;
AudioInputI2S micIn;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(micIn, 0, myDsp, 0);
AudioConnection patchCord1(myDsp,0,out,0);
AudioConnection patchCord2(myDsp,0,out,1);

void setup() {
  AudioMemory(6); // A 4 trop de bruit, 5 un peu mieux et après c'est bien...
  audioShield.enable();
  audioShield.volume(0.5);
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  // Configurez chaque filtre EQ
  myDsp.configurePeakEQFilter(0, 1000, 100, -3.0); 
}

void loop() {
  delay(100);
}
