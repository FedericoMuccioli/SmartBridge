#include <Arduino.h>
#include "SmartLightingTask.h"
#include "kernel/MsgService.h"
#include "config.h"

#define MSG(state) (state == ON ? String("ON") : state == OFF ? String("OFF") : String("DISABLE"))

SmartLightingTask::SmartLightingTask(SmartLighting* smartLighting){
  this->smartLighting = smartLighting;
}
  
void SmartLightingTask::init(int period){
  Task::init(period);
  smartLighting->init();
  state = OFF;
  MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + MSG(state));
}
  
void SmartLightingTask::tick(){
  switch (state){
    case OFF:
      if (smartLighting->isSomeoneDetected()){
        smartLighting->turnLightOn();
        state = ON;
        MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + MSG(state));
      }
      break;
    case ON:
      if (!(smartLighting->isSomeoneDetected())){
        smartLighting->turnLightOff();
        state = OFF;
        MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + MSG(state));
      }
      break;
  }
}

void SmartLightingTask::setActive(bool active){
  if (active){
    state = OFF;
  } else {
    smartLighting->init();
    state = DISABLE;
  }
  MsgService.sendMsg(SMART_LIGHTING_STATE_MSG + MSG(state));
  Task::setActive(active);
}