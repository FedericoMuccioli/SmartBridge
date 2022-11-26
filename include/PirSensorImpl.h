#ifndef __PIRSENSORIMPL__
#define __PIRSENSORIMPL__

#include "PirSensor.h"

class PirSensorImpl: public PirSensor {

public: 
  PirSensorImpl(int pin);
  bool isMoved();
  
private:
  int pin;
};

#endif

