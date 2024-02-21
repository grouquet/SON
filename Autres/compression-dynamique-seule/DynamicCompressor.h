#ifndef DynamicCompressor_h
#define DynamicCompressor_h

#include "Arduino.h"

class DynamicCompressor {
public:
    DynamicCompressor(float threshold, float ratio, float attack, float release);
    float processSample(float sample);

private:
    float threshold;
    float ratio;
    float attackTime;
    float releaseTime;
    float envelope;
    float gain;
    float sampleRate;

    float calculateGain(float sample);
    void updateEnvelope(float sample);
};

#endif
