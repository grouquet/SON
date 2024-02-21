#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS])
{
}

MyDsp::~MyDsp(){}

void MyDsp::configurePeakEQFilter(int index, float fx, float B, float Lfx) {
    if(index < 0 || index >= numEQFilters) return; // Vérifie l'indice

    float sampleRate = 44100.0; // Ou obtenir le taux d'échantillonnage dynamiquement si nécessaire -> c'est peut être ce qu'il faut faire d'ailleurs
    peakEQs[index].configurePeakEQ(fx, B, Lfx, sampleRate);
}



void MyDsp::update(void) {
    audio_block_t *inBlock, *outBlock;
    inBlock = receiveReadOnly(0); // Recevoir le bloc d'entrée du canal 0
    if (!inBlock) return; // Si pas de bloc d'entrée, rien à faire

    outBlock = allocate(); // Allouer un bloc de sortie
    if (!outBlock) {
        release(inBlock); // Si l'allocation échoue, libérer le bloc d'entrée et sortir
        return;
    }

    // Traitement de chaque échantillon
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = inBlock->data[i] * DIV_16; // Convertir en float pour le traitement
        
        // Appliquer le filtre
        for (int eq = 0; eq < numEQFilters; eq++) {
            currentSample = peakEQs[eq].tick(currentSample);
        }

        // Assurer que l'échantillon est dans les limites [-1.0, 1.0]
        currentSample = max(-1, min(1, currentSample));

        // Convertir l'échantillon traité en 16-bit et le stocker dans le bloc de sortie
        outBlock->data[i] = currentSample * MULT_16;
    }

    // Transmettre le bloc de sortie et libérer les blocs
    transmit(outBlock, 0); // Transmettre sur le canal 0
    release(inBlock);
    release(outBlock);
}
