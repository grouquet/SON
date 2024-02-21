#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord1(in, 0, myDsp, 0); // Connecter l'entrée à MyDsp pour traitement
AudioConnection patchCord2(myDsp, 0, out, 0); // Connecter la sortie de MyDsp à l'oreille gauche
AudioConnection patchCord3(in, 0, out, 1); // Connecter directement l'entrée à l'oreille droite (sans modification)

void setup() {
  Serial.begin(9600);
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(1);
  // Configurer les filtres + Changer nb filtres dans MyDsp.h !!
  myDsp.configurePeakEQFilter(0, 250, 150, 3.0); 
  myDsp.configurePeakEQFilter(1, 475, 175, 4.0); 
  myDsp.configurePeakEQFilter(2, 750, 250, 5.0); 
  myDsp.configurePeakEQFilter(3, 1050, 400, 6.0); 
  myDsp.configurePeakEQFilter(4, 1500, 500, 8.0); 
  myDsp.configurePeakEQFilter(5, 2000, 500, 10.0); 
  myDsp.configurePeakEQFilter(6, 2800, 600, 11.0); 
  myDsp.configurePeakEQFilter(7, 4200, 1000, 13.0); 
  myDsp.configurePeakEQFilter(8, 6000, 1000, 15.0); 
  myDsp.configurePeakEQFilter(9, 8000, 1000, 18.0); 

}

void loop() {
}
