#ifndef __SMARTLIGHTING__
#define __SMARTLIGHTING__

#include "Led.h"
#include "PirSensorImpl.h"
#include "LightSensorImpl.h"

class SmartLighting {

private:
  Light* led;
  PirSensor* pirSensor;
  LightSensor* lightSensor;
  volatile unsigned long time;
  const unsigned long T = 3000;
  const int THl = 400;

public:
  SmartLighting();
  void init();
  bool isSomeoneDetected();
  void turnLightOn();
  void turnLightOff();
};

#endif

