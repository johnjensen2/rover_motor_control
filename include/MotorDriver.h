// MotorDriver.h
#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
class MotorDriver {
public:
    void begin();
    void applyPWM(int pwm, bool forward);
    void stop();
    void testPins();   // add this
    float readCurrent();
private:
    void initPins();
};

#endif