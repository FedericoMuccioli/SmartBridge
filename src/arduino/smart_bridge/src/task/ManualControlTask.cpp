#include <Arduino.h>
#include "ManualControlTask.h"
#include "kernel/MsgService.h"
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/PotentiometerImpl.h"

#define HARDWARE_CONTROL_VALUE map(pot->getAdjustment(), 30, 1000, 0, 180)

#define MSG(state) (state == OFF ? String("false") : String("true"))

ManualControlTask::ManualControlTask(ManualControl* manualControl){
  this->manualControl = manualControl;
  this->button = new ButtonImpl(BUTTON_PIN);
  this->pot = new PotentiometerImpl(POT_PIN);
}
  
void ManualControlTask::init(int period){
  Task::init(period);
  emptyMsgBuffer();
  state = OFF;
}
  
void ManualControlTask::tick(){
  switch (state){
    case OFF:
      if(MsgService.isMsgAvailable()){
        String content = getContentMsg();
        if (content.indexOf('-') == 0){
          int value = -atoi(content.c_str());
          manualControl->setActive(true);
          manualControl->setValue(value);
          state = SOFTWARE;
          MsgService.sendMsg(MANUAL_CONTROL_MSG + MSG(state));
        }
      } else if (button->isPressed()){
        manualControl->setActive(true);
        manualControl->setValue(HARDWARE_CONTROL_VALUE);
        state = HARDWARE;
      }
      break;
    case SOFTWARE:
      if(MsgService.isMsgAvailable()){
        String content = getContentMsg();
        if (content.indexOf('-') == 0){
          manualControl->setActive(false);
          state = OFF;
          MsgService.sendMsg(MANUAL_CONTROL_MSG + MSG(state));
        } else {
          manualControl->setValue(atoi(content.c_str()));
        }
      }
      break;
    case HARDWARE:
      if (button->isPressed()){
        manualControl->setActive(false);
        emptyMsgBuffer();
        state = OFF;
      } else {
        manualControl->setValue(HARDWARE_CONTROL_VALUE);
      }
      break;
  }
}

void ManualControlTask::setActive(bool active){
  if (!active){
    state = OFF;
    MsgService.sendMsg(MANUAL_CONTROL_MSG + MSG(state));
    manualControl->setActive(false);
  } else {
    emptyMsgBuffer();
  }
  Task::setActive(active);
}

void ManualControlTask::emptyMsgBuffer(){
  if (MsgService.isMsgAvailable()){
    delete MsgService.receiveMsg();
  }
}

String ManualControlTask::getContentMsg(){
  Msg *msg = MsgService.receiveMsg();
  String string = msg->getContent();
  delete msg;
  return string;
}