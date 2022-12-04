#ifndef __MANUALCONTROL__
#define __MANUALCONTROL__

#include "devices/ButtonImpl.h"
#include "devices/PotentiometerImpl.h"

class ManualControl {

private:
  bool active;
  int value;

public:
  ManualControl();
  void init();
  void setValue(int value);
  void setActive(bool active);
  bool isActive();
  int getValue();
};

#endif

