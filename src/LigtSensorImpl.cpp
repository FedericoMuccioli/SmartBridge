#include <Arduino.h>
#include "LightSensorImpl.h"

LightSensorImpl::LightSensorImpl(int pin){
  this->pin = pin;
  pinMode(pin,INPUT);
}

int LightSensorImpl::getLightIntensity(){
  int lightIntesity = analogRead(pin);
  /*
  Serial.print("lightIntesity: ");//debug
  Serial.println(lightIntesity);//debug
  */
  return lightIntesity;
}
