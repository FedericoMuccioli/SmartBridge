#include <Arduino.h>
#include "ManualControlTask.h"
#include "kernel/MsgService.h"
#include "config.h"

ManualControlTask::ManualControlTask(ManualControl* manualControl){
  this->manualControl = manualControl;
  this->button = new ButtonImpl(BUTTON_PIN);
  this->pot = new PotentiometerImpl(POT_PIN);

}
  
void ManualControlTask::init(int period){
  Task::init(period);
  if (MsgService.isMsgAvailable()){//svuoto buffer
    delete MsgService.receiveMsg();
  }
  state = OFF;
}
  
void ManualControlTask::tick(){
  switch (state){
    case OFF:
      if(MsgService.isMsgAvailable()){
        Msg *msg = MsgService.receiveMsg();
        String content = msg->getContent();
        delete msg;
        if (content.indexOf('-') == 0){
        int value = -atoi(content.c_str());
        MsgService.sendMsg("ctrue");
        manualControl->setActive(true);
        manualControl->setValue(value);
        state = SOFTWARE;
        }
      } else if (button->isPressed()){
        manualControl->setActive(true);
        manualControl->setValue(map(pot->getAdjustment(), 10, 1000, 0, 180));
        state = HARDWARE;
      }
      break;

    case SOFTWARE:
      if(MsgService.isMsgAvailable()){
        Msg *msg = MsgService.receiveMsg();
        String content = msg->getContent();
        delete msg;
        if (content.indexOf('-') == 0){
          MsgService.sendMsg("cfalse");
          manualControl->setActive(false);
          state = OFF;
        } else {
          manualControl->setValue(atoi(content.c_str()));
        }
      }
      break;

    case HARDWARE:
      if (button->isPressed()){
        manualControl->setActive(false);
        if (MsgService.isMsgAvailable()){//svuoto buffer
          delete MsgService.receiveMsg();
        }
        state = OFF;
      } else {
        manualControl->setValue(map(pot->getAdjustment(), 10, 1000, 0, 180));
      }
      break;
  }
}

void ManualControlTask::setActive(bool active){//sistemare
  if (!active){
    MsgService.sendMsg("cfalse");
    manualControl->setActive(false);
    state = OFF;
  }
  Task::setActive(active);
}