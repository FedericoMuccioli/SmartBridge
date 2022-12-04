#include <Arduino.h>
#include "SmartLighting.h"
#include "devices/Led.h"
#include "devices/PirSensorImpl.h"
#include "devices/LightSensorImpl.h"
#include "config.h"


SmartLighting::SmartLighting(){
  led = new Led(LIGHT_PIN);
  pirSensor = new PirSensorImpl(PIR_PIN);
  lightSensor = new LightSensorImpl(PHOTO_PIN);
}

void SmartLighting::init(){
  time = 0;
  led->switchOff();
}

bool SmartLighting::isSomeoneDetected(){
  if (pirSensor->isMoved()){
    time = millis();
  }
  return (pirSensor->isMoved() || millis() - time < timeDetected) && lightSensor->getLightIntensity() <= lightThreshold;
}

void SmartLighting::turnLightOn(){
    led->switchOn();
}

void SmartLighting::turnLightOff(){
    led->switchOff();
}