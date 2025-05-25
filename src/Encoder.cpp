#include "Encoder.h"
#include <Arduino.h>

const byte ENCODER_PIN_A = 2;
const byte ENCODER_PIN_B = 3;

Encoder* encoderInstance = nullptr;

void onEncoderPulse() {
    if (!encoderInstance) return;
    if (digitalRead(ENCODER_PIN_B) == LOW) {
        encoderInstance->pulseCount++;
        encoderInstance->direction = true;
    } else {
        encoderInstance->pulseCount--;
        encoderInstance->direction = false;
    }
}

void Encoder::begin() {
    encoderInstance = this;
    pinMode(ENCODER_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_PIN_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), onEncoderPulse, RISING);
}

void Encoder::update() {
    // Optional: keep if you're doing something else here
}

float Encoder::getRPM() {
    static long lastCount = 0;
    static unsigned long lastTime = 0;
    unsigned long now = millis();
    if (now - lastTime < 100) return 0;
    long delta = pulseCount - lastCount;
    lastCount = pulseCount;
    lastTime = now;
    return (abs(delta) / 16.0) * 600.0; // 16 pulses/rev
}

long Encoder::getTicks() {
    return pulseCount;
}

bool Encoder::getDirection() {
    return direction;
}

void Encoder::reset() {
    noInterrupts();
    pulseCount = 0;
    interrupts();
}
