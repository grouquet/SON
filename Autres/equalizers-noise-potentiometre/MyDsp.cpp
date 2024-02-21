#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
noise()
{
}

MyDsp::~MyDsp(){}

void MyDsp::configurePeakEQFilter(int index, float fx, float B, float Lfx) {
    if(index < 0 || index >= numEQFilters) return; // Vérifie l'indice

    float sampleRate = 44100.0; // Ou obtenir le taux d'échantillonnage dynamiquement si nécessaire -> c'est peut être ce qu'il faut faire d'ailleurs
    peakEQs[index].configurePeakEQ(fx, B, Lfx, sampleRate);
}



void MyDsp::update(void) {
    audio_block_t* outBlock[AUDIO_OUTPUTS];
    for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
        outBlock[channel] = allocate();
        if (outBlock[channel]) {
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                float currentSample = noise.tick();
                
                // Applique chaque filtre EQ en série
                for(int eq = 0; eq < numEQFilters; eq++) {
                    currentSample = peakEQs[eq].tick(currentSample);
                }

                currentSample = max(-1, min(1, currentSample * 0.5));
                int16_t val = currentSample * MULT_16;
                outBlock[channel]->data[i] = val;
            }
            transmit(outBlock[channel], channel);
            release(outBlock[channel]);
        }
    }
}
