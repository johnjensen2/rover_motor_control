#include "ConfigManager.h"
#include <EEPROM.h>

void ConfigManager::load() {
    EEPROM.get(0, kp);
    EEPROM.get(4, ki);
    EEPROM.get(8, kd);
    if (kp <= 0 || kp > 10) { kp = 0.05; ki = 0.05; kd = 0.01; }
}

void ConfigManager::save(float pk, float ki_, float kd_) {
    EEPROM.put(0, pk);
    EEPROM.put(4, ki_);
    EEPROM.put(8, kd_);
    kp = pk; ki = ki_; kd = kd_;
}


float ConfigManager::getKp() { return kp; }
float ConfigManager::getKi() { return ki; }
float ConfigManager::getKd() { return kd; }
