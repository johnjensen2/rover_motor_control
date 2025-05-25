// src/MotionController.cpp
#include <Arduino.h>  // <-- Add this line
#include "MotionController.h"
#include "MotorDriver.h"
#include "Encoder.h"
#include "PIDController.h"
#include "ConfigManager.h"  // <-- Include if you need to access config values
#include "Diagnostics.h"  // <-- Include if you need diagnostics

MotionController::MotionController(MotorDriver* m, Encoder* e, PIDController* p)
: motor(m), encoder(e), pid(p) {}

void MotionController::update() {
    if (targetTicks > 0 && abs(encoder->getTicks()) >= targetTicks) {
        stop();
    }
}

void MotionController::moveDistance(float cm, float rpm) {
    const float wheelCircumference = 3.1416 * 25.4; // in cm
    long revolutions = cm / wheelCircumference;
    targetTicks = revolutions * 16; // pulses per revolution
    encoder->begin();
    encoder->reset();  // <-- You may want to add a reset method to Encoder
    pid->setTargetRPM(rpm);
}

void MotionController::stop() {
    pid->stop();
    targetTicks = 0;
}

