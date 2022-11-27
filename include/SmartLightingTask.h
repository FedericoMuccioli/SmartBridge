#ifndef __SMARTLIGHTINGTASK__
#define __SMARTLIGHTINGTASK__

#include "Task.h"
#include "Led.h"
#include "PirSensorImpl.h"
#include "LightSensorImpl.h"

class SmartLightingTask: public Task {

private:

  int pinLed;
  int pinPir;
  int pinLight;
  Light* led;
  PirSensor* pirSensor;
  LightSensor* lightSensor;
  enum { ON, OFF} state;

public:

  SmartLightingTask(int pinLed, int pinPir, int pinLight);  
  void init(int period);  
  void tick();
};

#endif

