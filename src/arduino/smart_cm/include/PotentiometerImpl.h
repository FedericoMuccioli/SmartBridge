#ifndef __POTENTIOMETERIMPL__
#define __POTENTIOMETERIMPL__

#include "Potentiometer.h"

class PotentiometerImpl: public Potentiometer {

public: 
  PotentiometerImpl(int pin);
  int getAdjustment();
  
private:
  int pin;
};

#endif
