#ifndef __MANUALCONTROLTASK__
#define __MANUALCONTROLTASK__

#include "kernel/Task.h"
#include "ManualControl.h"

class ManualControlTask: public Task {

private:
  enum {OFF, SOFTWARE, HARDWARE} state;
  ManualControl* manualControl;
  Button* button;
  Potentiometer* pot;

public:
  ManualControlTask(ManualControl* manualControl);  
  void init(int period);
  void tick();
  void setActive(bool active);
};

#endif
