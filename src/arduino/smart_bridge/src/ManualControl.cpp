#include <Arduino.h>
#include "ManualControl.h"
#include "config.h"
#include "kernel/MsgService.h"

ManualControl::ManualControl(){
  active = false;
  value = 0;
}

void ManualControl::setValue(int value){
  this->value = value;
}

void ManualControl::setActive(bool active){
  this->active = active;
}

bool ManualControl::isActive(){
  return active;
}

int ManualControl::getValue(){
  return value;
}
