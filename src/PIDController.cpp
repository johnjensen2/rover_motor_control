// src/PIDController.cpp

#include <Arduino.h>
#include "PIDController.h"
#include "ConfigManager.h"
#include "Encoder.h"


void PIDController::begin(float pk, float ki_, float kd_) {
    kp = pk;
    ki = ki_;
    kd = kd_;
    integral = 0;
    previousError = 0;
    lastTime = 0;
}

void PIDController::update(float currentRPM) {
    unsigned long now = millis();
    if (now - lastTime < 50) return;
    float error = targetRPM - currentRPM;
    integral += error * 0.05;
    float derivative = (error - previousError) / 0.05;
    float output = kp * error + ki * integral + kd * derivative;
    output = constrain(output, 0, 255);
    previousError = error;
    lastTime = now;
    Serial.print("PID output: ");
    Serial.println(output);
    motor->applyPWM((targetRPM >= 0), output);
}


void PIDController::setTargetRPM(float rpm) {
    targetRPM = rpm;
}

void PIDController::stop() {
    targetRPM = 0;
    integral = 0;
    previousError = 0;
    if (motor) {
        motor->stop();
    }
}

void PIDController::tune() {
    // Dummy tune logic or your real auto-tune
    kp = 0.1; ki = 0.05; kd = 0.01;
    ConfigManager().save(kp, ki, kd);
    Serial.print("Tuned PID: Kp=");
    Serial.print(kp);
    Serial.print(", Ki=");
    Serial.print(ki);
    Serial.print(", Kd=");
    Serial.println(kd);
}


void PIDController::autoTune(int cycles) {
    Serial.println("Starting PID Auto-Tune...");
    
    float bestKp = 0.05, bestKi = 0.05, bestKd = 0.01;
    float bestError = 1e6;

    for (int i = 0; i < cycles; i++) {
        // Simple sweep of values (can be replaced with more advanced logic later)
        float testKp = 0.03 + i * 0.01;
        float testKi = 0.03 + i * 0.005;
        float testKd = 0.005 + i * 0.002;

        // Set test parameters
        begin(testKp, testKi, testKd);
        setTargetRPM(5000); // Test RPM

        // Simulate/test for 1 second
        unsigned long start = millis();
        float accumulatedError = 0;

        while (millis() - start < 100) {
            float currentRPM = encoder->getRPM();  // You'll need encoder access
            update(currentRPM);
            accumulatedError += abs(targetRPM - currentRPM);
            delay(50);  // Simulated control period
        }

        Serial.print("Cycle "); Serial.print(i + 1);
        Serial.print(" Error: "); Serial.println(accumulatedError);

        if (accumulatedError < bestError) {
            bestError = accumulatedError;
            bestKp = testKp;
            bestKi = testKi;
            bestKd = testKd;
        }
    }

    // Save best results
    begin(bestKp, bestKi, bestKd);
    ConfigManager().save(bestKp, bestKi, bestKd);
    Serial.println("Auto-Tune Complete");
    Serial.print("Best Kp: "); Serial.println(bestKp);
    Serial.print("Best Ki: "); Serial.println(bestKi);
    Serial.print("Best Kd: "); Serial.println(bestKd);
}

void PIDController::setEncoder(Encoder* e) {
    encoder = e;
}


float PIDController::getKp() { return kp; }
float PIDController::getKi() { return ki; }
float PIDController::getKd() { return kd; }
