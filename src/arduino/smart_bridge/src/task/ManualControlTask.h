#ifndef __MANUALCONTROLTASK__
#define __MANUALCONTROLTASK__

#include "kernel/Task.h"
#include "ManualControl.h"
#include "devices/Button.h"
#include "devices/Potentiometer.h"

#define MANUAL_CONTROL_PERIOD 200

class ManualControlTask: public Task {
private:
  enum {OFF, SOFTWARE, HARDWARE, DISABLE} state;
  ManualControl* manualControl;
  Button* button;
  Potentiometer* pot;
  void emptyMsgBuffer();
  String getContentMsg();
public:
  ManualControlTask(ManualControl* manualControl);  
  void init(int period);
  void tick();
  void setActive(bool active);
};

#endif
