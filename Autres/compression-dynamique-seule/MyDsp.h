#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "DynamicCompressor.h"

class MyDsp : public AudioStream {
public:
    MyDsp();
    virtual ~MyDsp();
    virtual void update(void);
    
private:
    DynamicCompressor compressor;
};

#endif
