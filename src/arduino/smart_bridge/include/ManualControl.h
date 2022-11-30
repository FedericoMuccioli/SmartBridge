#ifndef __MANUALCONTROL__
#define __MANUALCONTROL__

#include "ButtonImpl.h"
#include "PotentiometerImpl.h"

class ManualControl {

private:
  Button* button;
  Potentiometer* potentiometer;

public:
  ManualControl();
  void startCheck();
  void endCheck();
  bool isActive();
  int getValue();
};

#endif

