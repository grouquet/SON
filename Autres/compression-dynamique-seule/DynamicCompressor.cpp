#include "DynamicCompressor.h"

DynamicCompressor::DynamicCompressor(float threshold, float ratio, float attack, float release)
: threshold(threshold), ratio(ratio), attackTime(attack), releaseTime(release), envelope(0.0), gain(1.0), sampleRate(44100.0) // Assurez-vous d'ajuster le sampleRate selon votre configuration
{
}

float DynamicCompressor::processSample(float sample) {
    updateEnvelope(sample);
    float compressedSample = sample * gain;
    return compressedSample;
}

void DynamicCompressor::updateEnvelope(float sample) {
    float sampleAbs = fabs(sample);
    // Attack ou release de l'enveloppe
    if (sampleAbs > envelope) {
        envelope += (sampleAbs - envelope) * (1.0 - exp(-1.0 / (attackTime * sampleRate)));
    } else {
        envelope += (sampleAbs - envelope) * (1.0 - exp(-1.0 / (releaseTime * sampleRate)));
    }
    gain = calculateGain(envelope);
}

float DynamicCompressor::calculateGain(float envelope) {
    // Convertir l'enveloppe (amplitude) en dB
    float envelopeDB = 20.0 * log10(envelope);

    // Vérifier si l'enveloppe dépasse le seuil
    if (envelopeDB > threshold) {
        // Calculer la différence en dB au-dessus du seuil
        float diffDB = envelopeDB - threshold;
        
        // Appliquer le ratio de compression
        float compressedDiffDB = diffDB / ratio;
        
        // Calculer le niveau dB après compression
        float compressedDB = threshold + compressedDiffDB;
        
        // Convertir le niveau dB compressé en gain linéaire
        float gain = pow(10, (compressedDB - envelopeDB) / 20.0);
        return gain;
    } else {
        // Pas de compression si l'enveloppe est en dessous du seuil
        return 1.0;
    }
}
