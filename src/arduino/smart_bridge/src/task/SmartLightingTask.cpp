#include <Arduino.h>
#include "SmartLightingTask.h"
#include "kernel/MsgService.h"
#include "config.h"

SmartLightingTask::SmartLightingTask(SmartLighting* smartLighting){
  this->smartLighting = smartLighting;
}
  
void SmartLightingTask::init(int period){
  Task::init(period);
  smartLighting->init();
  state = OFF;
}
  
void SmartLightingTask::tick(){
  switch (state){
    case OFF:
      if (smartLighting->isSomeoneDetected()){
        smartLighting->turnLightOn();
        state = ON;
      }
      break;
    case ON:
      if (!(smartLighting->isSomeoneDetected())){
        smartLighting->turnLightOff();
        state = OFF;
      }
      break;
  }
  MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + String(state));
}

void SmartLightingTask::setActive(bool active){
  if (!active){
    smartLighting->init();
    MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + String(state));
  }
  Task::setActive(active);
}