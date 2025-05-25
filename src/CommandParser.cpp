// src/CommandParser.cpp
#include "CommandParser.h"
#include <Arduino.h>
#include "MotionController.h"
#include "PIDController.h"
#include "MotorDriver.h"
#include "Encoder.h"
#include "ConfigManager.h"
#include "Diagnostics.h"





CommandParser::CommandParser(MotionController* m, PIDController* p) : motion(m), pid(p) {}

void CommandParser::processSerial() {
    if (!Serial.available()) return;
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.startsWith("D")) {
        int rIndex = input.indexOf("R");
        float dist = input.substring(1, rIndex).toFloat();
        float rpm = input.substring(rIndex + 1).toFloat();
        motion->moveDistance(dist, rpm);
    } else if (input.startsWith("R")) {
        float rpm = input.substring(1).toFloat();
        pid->setTargetRPM(rpm);
    } else if (input.equalsIgnoreCase("TUNE")) {
        pid->tune();
    } else if (input.equalsIgnoreCase("ESTOP")) {
        pid->stop();
    }else if (input.equalsIgnoreCase("AUTOTUNE")) {
    pid->autoTune(10);
    } else if (input.equalsIgnoreCase("TEST")) {
    motion->getMotor()->testPins();
    }else if (input.startsWith("PWM")) {
    int pwmValue = input.substring(3).toInt();
    pwmValue = constrain(pwmValue, 0, 255);
    motion->getMotor()->applyPWM(true, pwmValue);
    Serial.print("Direct PWM: ");
    Serial.println(pwmValue);
}

}

