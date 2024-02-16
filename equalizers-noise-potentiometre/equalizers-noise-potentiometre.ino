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
  pinMode(A0, INPUT); // Configure A0 comme entrée
  Serial.begin(9600);
  // Configurez chaque filtre EQ
  myDsp.configurePeakEQFilter(0, 150, 200, 10.0); 
   
}
void loop() {
  int potValue = analogRead(A0); // Lire la valeur du potentiomètre
  // Mapper la valeur lue (0-1023) à la plage de fréquences (150-5000 Hz)
  float frequency = map(potValue, 0, 1023, 150, 5000);

  // Afficher la valeur lue et la fréquence mappée dans le moniteur série
  Serial.print("Valeur Potentiomètre: ");
  Serial.print(potValue);
  Serial.print(", Fréquence: ");
  Serial.println(frequency);

  // Reconfigurer le filtre EQ avec la nouvelle fréquence
  myDsp.configurePeakEQFilter(0, frequency, 100, 10.0);

  delay(100); // Un délai pour limiter la fréquence de mise à jour
}
