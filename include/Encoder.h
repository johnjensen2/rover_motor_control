#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
public:
    void begin();
    void update();
    float getRPM();
    long getTicks();
    bool getDirection();
    void reset();


    volatile long pulseCount = 0;
    volatile bool direction = true;
};

#endif
