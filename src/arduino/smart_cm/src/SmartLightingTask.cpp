#include <Arduino.h>
#include "SmartLightingTask.h"
#include "MsgService.h"


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
  //MsgService.sendMsg("light: " + String(state));
}

  void SmartLightingTask::setActive(bool active){
    if (!active){
      led->switchOff();
      state = OFF;
      time = 0;
      MsgService.sendMsg("light: " + String(state));
    }
    Task::setActive(active);
  }