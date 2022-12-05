#include <Arduino.h>
#include "config.h"
#include "SmartLighting.h"
#include "devices/Led.h"
#include "devices/PirSensorImpl.h"
#include "devices/LightSensorImpl.h"

#define LIGHT_THRESHOLD 400
#define PIR_TOLLERANCE_TIME 1000

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
  return (pirSensor->isMoved() || millis() - time < PIR_TOLLERANCE_TIME) 
      && lightSensor->getLightIntensity() <= LIGHT_THRESHOLD;
}

void SmartLighting::turnLightOn(){
    led->switchOn();
}

void SmartLighting::turnLightOff(){
    led->switchOff();
}