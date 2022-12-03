#include <Arduino.h>
#include "ManualControl.h"
#include "config.h"
#include "MsgService.h"

//Usare polling anzichè interrupt, per quest di sincronia e sicurezza.
bool manualControl = false;
bool manualControlJava = false;
String string;
unsigned long lastTimePressed = 0;


void buttonHandler(void){
  if( millis() - lastTimePressed > 200){
  manualControl = !manualControl;
  lastTimePressed = millis();
  }
}

ManualControl::ManualControl(){
  button = new ButtonImpl(BUTTON_PIN);
  potentiometer = new PotentiometerImpl(POT_PIN);
}

void ManualControl::startCheck(){
  manualControl = false;
  manualControlJava = false;//
  if (MsgService.isMsgAvailable()){
    delete MsgService.receiveMsg();//svuoto buffer
  }
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonHandler, RISING);
}

void ManualControl::endCheck(){
  detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
}

bool ManualControl::isActive(){
  return MsgService.isMsgAvailable() || manualControl;
}

int ManualControl::getValue(){
  if (MsgService.isMsgAvailable()){
    Msg *msg = MsgService.receiveMsg();
    int value =  atoi(msg->getContent().c_str());
    delete msg;
    return value;
  }
  return map(potentiometer->getAdjustment(), 10, 1000, 0, 180);
}
