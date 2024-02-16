#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "Noise.h"
#include "Biquad.h"

class MyDsp : public AudioStream {
public:
    MyDsp();
    virtual ~MyDsp();
    virtual void update(void);
    void configurePeakEQFilter(int index, float fx, float B, float Lfx);
    // Ajoutez d'autres méthodes pour configurer le filtre, si nécessaire
private:
    static const int numEQFilters = 1; // Par exemple, pour trois filtres EQ
    Biquad peakEQs[numEQFilters];
    Noise noise;
    float threshold = -20; // Seuil de compression en dB
    float ratio = 4.0; // Ratio de compression
    float attack = 0.01; // Temps d'attaque en secondes
    float release = 0.1; // Temps de relâchement en secondes
    float gainReduction = 1.0; // Réduction de gain actuelle
};

#endif
