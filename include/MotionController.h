// MotionController.h
#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H
#include "MotorDriver.h"
#include "Encoder.h"
#include "PIDController.h"
class MotionController {
public:
    MotionController(MotorDriver* m, Encoder* e, PIDController* p);
    void update();
    void moveDistance(float cm, float rpm);
    void stop();
    MotorDriver* getMotor() { return motor; }   // <-- Add this getter
private:
    MotorDriver* motor;
    Encoder* encoder;
    PIDController* pid;
    long targetTicks = 0;
};
#endif
