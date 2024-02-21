#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.5);
  // Configurez chaque filtre EQ
  myDsp.configurePeakEQFilter(0, 1000, 100, 3.0); 
  myDsp.configurePeakEQFilter(1, 12000, 100, -3.0); 
  myDsp.configurePeakEQFilter(2, 2000, 100, 3.0); 
}

void loop() {
  delay(100);
}
