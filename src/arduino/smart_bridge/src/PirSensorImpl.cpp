#include <Arduino.h>
#include "PirSensorImpl.h"

PirSensorImpl::PirSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

bool PirSensorImpl::isMoved(){
  bool isMoved = (digitalRead(pin) == HIGH);
  /*debug
  Serial.print("isMoved? ");
  Serial.println(isMoved);
  */
  return isMoved;
}
