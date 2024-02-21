#ifndef Biquad_h_
#define Biquad_h_

class Biquad {
public:
    Biquad();
    void setCoefficients(float b0, float b1, float b2, float a1, float a2);
    float tick(float input);
    void configurePeakEQ(float fx, float B, float Lfx, float SR);

private:
    float db2linear(float dB);
    float b0, b1, b2, a1, a2;
    float x1, x2, y1, y2;
};

#endif
