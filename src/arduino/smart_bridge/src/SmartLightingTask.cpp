#include <Arduino.h>
#include "SmartLightingTask.h"
#include "MsgService.h"


SmartLightingTask::SmartLightingTask(SmartLighting* smartLighting){
  this->smartLighting = smartLighting;
}
  
void SmartLightingTask::init(int period){
  Task::init(period);
  smartLighting->init();
  state = DARK;
}
  
void SmartLightingTask::tick(){

  switch (state){//aggiungere stato sospesa
    case DARK:
      if (smartLighting->isSomeoneDetected()){
        smartLighting->turnLightOn();
        state = LIGHT;
      }
      break;
    case LIGHT:
      if (!(smartLighting->isSomeoneDetected())){
        smartLighting->turnLightOff();
        state = DARK;
      }
      break;
  }
  //MsgService.sendMsg("light: " + String(state));
}

  void SmartLightingTask::setActive(bool active){//sistemare
    if (!active){
      smartLighting->init();
      state = DARK;
      MsgService.sendMsg("light: " + String(state));
    }
    Task::setActive(active);
  }