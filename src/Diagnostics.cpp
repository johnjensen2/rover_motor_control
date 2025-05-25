// src/Diagnostics.cpp
#include "Diagnostics.h"
#include <Arduino.h>

Diagnostics::Diagnostics(MotorDriver* m, Encoder* e, PIDController* p)
: motor(m), encoder(e), pid(p) {}

void Diagnostics::begin() {}

void Diagnostics::report() {
    static unsigned long lastReport = 0;
    if (millis() - lastReport >= 500) {
        lastReport = millis();
        Serial.print("RPM: "); Serial.print(encoder->getRPM());
        Serial.print(" | Dir: "); Serial.print(encoder->getDirection() ? "FWD" : "REV");
        Serial.print(" | Ticks: "); Serial.print(encoder->getTicks());
        Serial.print(" | Current: "); Serial.println(motor->readCurrent());
    }
}
