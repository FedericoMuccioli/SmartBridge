#ifndef __SMARTLIGHTINGTASK__
#define __SMARTLIGHTINGTASK__

#include "kernel/Task.h"
#include "SmartLighting.h"

#define SMART_LIGHTING_PERIOD 100

class SmartLightingTask: public Task {

private:
  enum {OFF, ON} state;
  SmartLighting* smartLighting;

public:
  SmartLightingTask(SmartLighting* smartLighting);  
  void init(int period);  
  void tick();
  void setActive(bool active);
};

#endif
