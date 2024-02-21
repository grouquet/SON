#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

MyDsp::MyDsp() : AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]), compressor(-40, 8, 0.01, 0.1)
{
}

MyDsp::~MyDsp(){}

//Configure un filtre
void MyDsp::configurePeakEQFilter(int index, float fx, float B, float Lfx) {
    if(index < 0 || index >= numEQFilters) return; 

    float sampleRate = AUDIO_SAMPLE_RATE_EXACT; 
    peakEQs[index].configurePeakEQ(fx, B, Lfx, sampleRate);
}


//Fonction de callback
void MyDsp::update(void) {
    audio_block_t *inBlock, *outBlock;
    inBlock = receiveReadOnly(0); // Recevoir le bloc d'entrée du canal 0
    if (!inBlock) return; 

    outBlock = allocate(); 
    if (!outBlock) {
        release(inBlock); 
        return;
    }

    // Traitement de chaque échantillon
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = inBlock->data[i] * DIV_16; 
        
        // Application des filtres en série
        for (int eq = 0; eq < numEQFilters; eq++) {
            currentSample = peakEQs[eq].tick(currentSample);
        }
         //Compression dynamique si nécessaire en sortie des filtres
        currentSample = compressor.processSample(currentSample);
       
        currentSample = max(-1, min(1, currentSample));

        outBlock->data[i] = currentSample * MULT_16;
    }

    // Transmettre le bloc de sortie et libérer les blocs
    transmit(outBlock, 0); // Transmettre sur le canal 0
    release(inBlock);
    release(outBlock);
}
