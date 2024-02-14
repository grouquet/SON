#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS])
{}

MyDsp::~MyDsp(){}

void MyDsp::configurePeakEQFilter(int index, float fx, float B, float Lfx) {
    if(index < 0 || index >= numEQFilters) return;
    
    float sampleRate = 44100.0; // Ou une méthode pour obtenir le SR actuel
    peakEqs[index].configurePeakEQ(fx, B, Lfx, sampleRate);
}

void MyDsp::configureHighPassFilter(float freq, float q) {
    highPassFilter.setHighpass(0, freq, q);
}




void MyDsp::update(void) {
  audio_block_t *inBlock, *outBlock[AUDIO_OUTPUTS];
  inBlock = receiveReadOnly(0); 
  
  if (!inBlock) return;
    
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float inputSample = inBlock->data[i] * DIV_16;
        float processedSample = inputSample; 
        for (int eq=0; eq< numEQFilters; eq++) {
          processedSample = peakEqs[eq].tick(inputSample)*0.5;
        }
        processedSample = max(-1,min(1,processedSample));
        int16_t val = processedSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
  release(inBlock);
}
