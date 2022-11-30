#ifndef __SMARTLIGHTINGTASK__
#define __SMARTLIGHTINGTASK__

#include "Task.h"
#include "SmartLighting.h"

class SmartLightingTask: public Task {

private:
  SmartLighting* smartLighting;
  enum {DARK, LIGHT} state;

public:
  SmartLightingTask(SmartLighting* smartLighting);  
  void init(int period);  
  void tick();
  void setActive(bool active);
};

#endif
