#include <Arduino.h>
#include "SmartLightingTask.h"


SmartLightingTask::SmartLightingTask(int pinLed, int pinPir, int pinLight){
  this->pinLed = pinLed;
  this->pinPir = pinPir;
  this->pinLight = pinLight;
}
  
void SmartLightingTask::init(int period){
  Task::init(period);
  led = new Led(pinLed);
  pirSensor = new PirSensorImpl(pinPir);
  lightSensor = new LightSensorImpl(pinLight);
  state = OFF;
}
  
void SmartLightingTask::tick(){
  switch (state){
    case OFF:
      led->switchOff();
      if (pirSensor->isMoved() && lightSensor->getLightIntensity() < THl){
        state = ON;
        time = millis();
      }
      break;
    case ON:
      led->switchOn();
      if (pirSensor->isMoved()){
        time = millis();
      }
      if (millis() - time >= T || lightSensor->getLightIntensity() > THl){
        state = OFF;
      }
      break;
  }
  
}
