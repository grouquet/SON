#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"


class MyDsp : public AudioStream {
public:
    MyDsp();
    virtual ~MyDsp();
    virtual void update(void);
    // Ajoutez d'autres méthodes pour configurer le filtre, si nécessaire
private:
    float threshold = -3; // Seuil de compression en dB
    float ratio = 4.0; // Ratio de compression
    float attack = 0.01; // Temps d'attaque en secondes
    float release = 0.1; // Temps de relâchement en secondes
    float gainReduction = 1.0; // Réduction de gain actuelle
};

#endif
