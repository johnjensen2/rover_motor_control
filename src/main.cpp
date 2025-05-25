// main.cpp
#include <Arduino.h>
#include "MotorDriver.h"
#include "Encoder.h"
#include "PIDController.h"
#include "MotionController.h"
#include "CommandParser.h"
#include "Diagnostics.h"
#include "ConfigManager.h"

MotorDriver motor;
Encoder encoder;
PIDController pid;
MotionController motion(&motor, &encoder, &pid);
CommandParser parser(&motion, &pid);
Diagnostics diag(&motor, &encoder, &pid);
ConfigManager config;

void setup() {
    Serial.begin(115200);
    encoder.begin();
    motor.begin();
       config.load();
    pid.begin(config.getKp(), config.getKi(), config.getKd());
    pid.setMotor(&motor);
    pid.setEncoder(&encoder);

    diag.begin();
    Serial.println("R.O.V.E.R Motor Controller Ready");
   
}

void loop() {
    encoder.update();
    motion.update();
    pid.update(encoder.getRPM());
    parser.processSerial();
   // diag.report();
}

