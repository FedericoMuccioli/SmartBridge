#include "Arduino.h"
#include "PotentiometerImpl.h"

PotentiometerImpl::PotentiometerImpl(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

int PotentiometerImpl::getAdjustment(){
  return analogRead(pin);
}
