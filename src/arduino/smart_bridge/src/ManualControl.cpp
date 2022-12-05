#include <Arduino.h>
#include "ManualControl.h"

ManualControl::ManualControl(){
  active = false;
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
