#include <Audio.h>
#include "MyDsp.h"

MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord1(in, 0, myDsp, 0); // Connecter l'entrée à MyDsp pour traitement
AudioConnection patchCord2(myDsp, 0, out, 0); // Connecter la sortie de MyDsp à l'oreille gauche
AudioConnection patchCord3(myDsp, 0, out, 1); // Connecter directement l'entrée à l'oreille droite

void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(1);
}

void loop() {
}
