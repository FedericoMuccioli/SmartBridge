#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__

#include "devices/Light.h"
#include "devices/PirSensor.h"
#include "devices/LightSensor.h"

class SmartLighting {
private:
  Light* led;
  PirSensor* pirSensor;
  LightSensor* lightSensor;
  volatile unsigned long time;

public:
  SmartLighting();
  void init();
  bool isSomeoneDetected();
  void turnLightOn();
  void turnLightOff();
};

#endif

