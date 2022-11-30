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
  const unsigned long timeDetected = 2000;
  const int lightThreshold = 400;

public:
  SmartLighting();
  void init();
  bool isSomeoneDetected();
  void turnLightOn();
  void turnLightOff();
};

#endif

