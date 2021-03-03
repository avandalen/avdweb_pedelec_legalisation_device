#ifndef PLD_H
#define PLD_H
 
#include "FreqPeriodCounter.h"

class Pas: public FreqPeriodCounter
{
public:
  Pas(byte pin, unsigned long timeOut, unsigned debounceTime);
  bool poll();
  
  bool pedalForward;  
  
private:
  unsigned long timeOut;
};

void openDrain1(byte pin, bool value);
void blinkLed1(byte pin, int n=3);
void repeatLed();
void calibrateTimer();
void brakeIfBrokenWheelSensor();
void brake(bool brake);
bool limpMode();

#endif
