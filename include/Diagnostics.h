// Diagnostics.h
#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H
#include "MotorDriver.h"
#include "Encoder.h"
#include "PIDController.h"
class Diagnostics {
public:
    Diagnostics(MotorDriver* m, Encoder* e, PIDController* p);
    void begin();
    void report();
private:
    MotorDriver* motor;
    Encoder* encoder;
    PIDController* pid;
};
#endif