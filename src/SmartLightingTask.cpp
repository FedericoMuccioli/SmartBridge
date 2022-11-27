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
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}
