#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"



#include "Biquad.h"

class MyDsp : public AudioStream {
public:
    MyDsp();
    virtual ~MyDsp();
    virtual void update(void);
    void configurePeakEQFilter(int index, float fx, float B, float Lfx);
    void configureHighPassFilter(float freq, float q);
    // Ajoutez d'autres méthodes pour configurer le filtre, si nécessaire
private:
    static const int numEQFilters = 3; 
    AudioFilterBiquad highPassFilter;
    Biquad peakEqs[numEQFilters];
    
};

#endif
