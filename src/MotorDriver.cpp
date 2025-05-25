#include "MotorDriver.h"
#include <Arduino.h>

const int RPWM = 5;
const int LPWM = 6;
const int REN = 7;
const int LEN = 8;

void MotorDriver::begin() {
    initPins();
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);
}

void MotorDriver::initPins() {
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(REN, OUTPUT);
    pinMode(LEN, OUTPUT);
}

void MotorDriver::applyPWM(int pwm, bool forward) {
    pwm = constrain(pwm, 0, 255);
    if (forward) {
        analogWrite(RPWM, pwm);
        analogWrite(LPWM, 0);
    } else {
        analogWrite(RPWM, 0);
        analogWrite(LPWM, pwm);
    }
}

void MotorDriver::stop() {
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
}

float MotorDriver::readCurrent() {
    // Placeholder for reading R_IS/L_IS
    return 0.0;
}


void MotorDriver::testPins() {
    initPins();
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);

    Serial.println("Forward full speed");
    analogWrite(RPWM, 255);
    analogWrite(LPWM, 0);
    delay(3000);

    Serial.println("Reverse full speed");
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 255);
    delay(3000);

    Serial.println("Stop");
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
}