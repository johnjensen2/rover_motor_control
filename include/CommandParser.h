
// CommandParser.h
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "MotionController.h"
#include "PIDController.h"
class CommandParser {
public:
    CommandParser(MotionController* m, PIDController* p);
    void processSerial();
private:
    MotionController* motion;
    PIDController* pid;
};
#endif