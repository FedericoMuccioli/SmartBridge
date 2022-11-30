#ifndef __SMARTLIGHTINGTASK__
#define __SMARTLIGHTINGTASK__

#include "Task.h"
#include "SmartLighting.h"

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
