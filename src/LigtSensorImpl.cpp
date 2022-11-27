#include <Arduino.h>
#include "LightSensorImpl.h"

LightSensorImpl::LightSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

int LightSensorImpl::getLightIntensity(){
  return analogRead(pin);
}
