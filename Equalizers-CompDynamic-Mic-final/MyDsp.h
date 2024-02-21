#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "Biquad.h"
#include "DynamicCompressor.h"

class MyDsp : public AudioStream {
public:
    MyDsp();
    virtual ~MyDsp();
    virtual void update(void);
    void configurePeakEQFilter(int index, float fx, float B, float Lfx);
    // Ajoutez d'autres méthodes pour configurer le filtre, si nécessaire
private:
    static const int numEQFilters = 10; 
    Biquad peakEQs[numEQFilters];
    DynamicCompressor compressor;
};

#endif
