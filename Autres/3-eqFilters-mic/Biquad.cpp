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
    float Bw = B * T / sin(wx * T);
    float a1 = M_PI * Bw;
    float g = db2linear(abs(Lfx));
    float b1 = g * a1;

    float b1s, a1s;
    if (Lfx > 0) {
        b1s = b1;
        a1s = a1;
    } else {
        b1s = a1;
        a1s = b1;
    }

    // Les coefficients b0 et b2 sont configurés pour avoir une influence neutre dans ce cas.
    setCoefficients(1.0, b1s, 1.0, a1s, 1.0);
}
