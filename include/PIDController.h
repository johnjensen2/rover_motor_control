#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>   // <-- include for abs, constrain, millis
#include "MotorDriver.h"
#include "Encoder.h"


class PIDController {
public:
    void begin(float, float, float);
    void update(float);
    void setTargetRPM(float);
    void stop();
    void tune();
    void setMotor(MotorDriver* m) { motor = m; }
    float getKp();
    float getKi();
    float getKd();
    void autoTune(int cycles = 10);
    void setEncoder(Encoder* e);

private:
    float kp, ki, kd;
    float targetRPM;
    float integral;
    float previousError;
    unsigned long lastTime;
    MotorDriver* motor;  // <-- was missing
    Encoder* encoder = nullptr; // pointer to Encoder object

};

#endif
