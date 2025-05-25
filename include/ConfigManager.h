// ConfigManager.h
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
class ConfigManager {
public:
    void load();
    void save(float kp, float ki, float kd);
    float getKp();
    float getKi();
    float getKd();
private:
    float kp = 0.05, ki = 0.05, kd = 0.01;
};
#endif
