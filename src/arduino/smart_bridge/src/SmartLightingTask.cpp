#include <Arduino.h>
#include "SmartLightingTask.h"
#include "MsgService.h"

SmartLightingTask::SmartLightingTask(SmartLighting* smartLighting){
  this->smartLighting = smartLighting;
}
  
void SmartLightingTask::init(int period){
  Task::init(period);
  smartLighting->init();
  state = OFF;
}
  
void SmartLightingTask::tick(){

  switch (state){//aggiungere stato sospesa
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
  MsgService.sendMsg("l" + String(state));
}

void SmartLightingTask::setActive(bool active){//sistemare
  if (!active){
    smartLighting->init();
    state = OFF;
    //MsgService.sendMsg("light: " + String(state));
  }
  Task::setActive(active);
}