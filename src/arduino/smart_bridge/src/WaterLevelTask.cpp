#include <Arduino.h>
#include "WaterLevelTask.h"
#include "MsgService.h"


//unsigned long time; //cancellare

WaterLevelTask::WaterLevelTask(int pinLedG, int pinLedR, int pinTrigSonar, int pinEchoSonar, 
    int pinMotor, int addrLcd, int rowsLcd, int colsLcd, Active* smartLight, ManualControlTask* manualControlTask, ManualControl* manualControl){
  this->pinLedG = pinLedG;
  this->pinLedR = pinLedR;
  this->pinTrigSonar = pinTrigSonar;
  this->pinEchoSonar = pinEchoSonar;
  this->pinMotor = pinMotor;
  this->addrLcd = addrLcd;
  this->colsLcd = colsLcd;
  this->rowsLcd = rowsLcd;
  this->smartLight = smartLight;
  this->manualControl = manualControl;
  this->manualControlTask = manualControlTask;

}
  
void WaterLevelTask::init(int period){
  Task::init(period);
  ledG = new Led(pinLedG);
  ledR = new Led(pinLedR);
  sonar = new SonarImpl(pinTrigSonar,pinEchoSonar);
  motor = new ServoMotorImpl(pinMotor);
  lcd = new LiquidCrystal_I2C(addrLcd,colsLcd,rowsLcd);
  lcd->init();
  motor->on();
  motor->setPosition(0);
  manualControlTask->setActive(false);
  setNormalState();
}

void WaterLevelTask::tick(){
  distance = (int)(sonar->getDistance()*100);
  switch (state){
    case NORMAL:
      if (distance <= WL_NORMAL && distance > WL_PRE_ALARM){//PRE_ALARM
        setPreAlarmState();
      } else if (distance <= WL_PRE_ALARM){//ALARM
        setAlarmState();
      }
      break;

    case PRE_ALARM:
      if(distance > WL_NORMAL){//NORMAL
        setNormalState();
      } else if(distance <= WL_PRE_ALARM){//ALARM
        setAlarmState();
      } else {
        blinkLedR();
        displayPreAlarm();
      }
      break;

    case ALARM:
      if (distance > WL_PRE_ALARM){
        motor->setPosition(0);
        smartLight->setActive(true);
        manualControlTask->setActive(false);
        if(distance > WL_NORMAL){//NORMAL
          setNormalState();
        } else if (distance <= WL_NORMAL && distance > WL_PRE_ALARM){//PRE_ALARM
          setPreAlarmState();
        }
      } else {
        int angle = manualControl->isActive() ? manualControl->getValue() :  map(distance, WL_PRE_ALARM, WL_MAX, 0, 180);//fare macro
        motor->setPosition(angle);
        displayAlarm();
      }
      break;
  }
  MsgService.sendMsg("w" + String(state));
  MsgService.sendMsg("v" + String(distance));
}

void WaterLevelTask::setNormalState(){
  ledG->switchOn();
  ledR->switchOff();
  lcd->noBacklight();
  Task::init(SAMPLING_NORMAL);
  state = NORMAL;
}

void WaterLevelTask::setPreAlarmState(){
  timeChangeLedR = 0;
  ledG->switchOn();
  blinkLedR();
  displayPreAlarm();
  Task::init(SAMPLING_PRE_ALARM);
  state = PRE_ALARM;
}

void WaterLevelTask::setAlarmState(){
  ledR->switchOn();
  ledG->switchOff();
  smartLight->setActive(false);
  manualControlTask->setActive(true);
  int angle = manualControl->isActive() ? map(manualControl->getValue(), 10, 1000, 0, 180) :  map(distance, WL_PRE_ALARM, WL_MAX, 0, 180);//fare macro
  if (MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    String string = msg->getContent();
    angle = string.toInt();
    delete msg;
  }
  motor->setPosition(angle);
  displayAlarm();
  Task::init(SAMPLING_ALARM);
  state = ALARM;
}

void WaterLevelTask::blinkLedR(){
  if (millis() - timeChangeLedR >= T_BLINK_LEDR){
    ledR->switchLight();
    timeChangeLedR = millis();
  }
}

void WaterLevelTask::displayPreAlarm(){
  lcd->backlight();
  lcd->clear();
  lcd->backlight();
  lcd->print("PRE ALARM");
  lcd->setCursor(0,2);
  lcd->print("Water Level: ");
  lcd->print(distance);
}

void WaterLevelTask::displayAlarm(){
  lcd->backlight();
  lcd->clear();
  lcd->print("ALARM");
  lcd->setCursor(0,2);
  lcd->print("Water Level: ");
  lcd->print(distance);
  lcd->setCursor(0,3);
  lcd->print("Valve degrees: ");
  lcd->print(motor->getPosition());
}
      