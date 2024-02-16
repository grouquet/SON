#include "Arduino.h"
#include "Biquad.h"
#include <cmath>


Biquad::Biquad() : b0(1), b1(0), b2(0), a1(0), a2(0), x1(0), x2(0), y1(0), y2(0) {}

void Biquad::setCoefficients(float b0, float b1, float b2, float a1, float a2) {
    this->b0 = b0;
    this->b1 = b1;
    this->b2 = b2;
    this->a1 = a1;
    this->a2 = a2;
}

float Biquad::tick(float input) {
    float output = b0*input + b1*x1 + b2*x2 - a1*y1 - a2*y2;
    x2 = x1;
    x1 = input;
    y2 = y1;
    y1 = output;
    return output;
}

//pas obligé de faire une classe attachée à Biquad ?
float Biquad::db2linear(float dB) {
    return pow(10.0, dB / 20.0);
}

void Biquad::configurePeakEQ(float fx, float B, float Lfx, float SR) {
    float T = 1.0 / SR;
    float wx = 2 * M_PI * fx;
    float Bw = B * T / sin(wx * T / 2); // Correction ici pour utiliser wx*T/2
    float a1 = M_PI * Bw;
    float g = db2linear(abs(Lfx));
    float b1 = g * a1;

    float b0 = 1.0; // Valeur initiale de b0 avant la transformation
    float b1s, a1s, b2 = 1.0; // b2 est configuré pour avoir une influence neutre, similaire à b0
    
    if (Lfx > 0) {
        b1s = b1;
        a1s = a1;
    } else {
        b1s = a1;
        a1s = b1;
    }

    // Application de la transformée bilinéaire
    float w1 = 2 * M_PI * fx;
    float c = 1 / tan(w1 * 0.5 / SR);
    float csq = c * c;
    float d = 1 + a1s * c + csq; // Assumant a0 = 1 pour la simplicité, a1 = a1s dans ce cas
    float b0d = (b0 + b1s * c + csq) / d;
    float b1d = 2 * (b0 - csq) / d;
    float b2d = (b0 - b1s * c + csq) / d;
    float a1d = 2 * (1 - csq) / d; // a0 = 1
    float a2d = (1 - a1s * c + csq) / d;

    setCoefficients(b0d, b1d, b2d, a1d, a2d);
}
