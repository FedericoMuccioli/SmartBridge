#include <Arduino.h>
#include "WaterLevelTask.h"

bool manualControl;

void buttonHandler(void){
  manualControl = !manualControl;
}

WaterLevelTask::WaterLevelTask(int pinLedG, int pinLedR, int pinTrigSonar, int pinEchoSonar, 
    int pinMotor, int addrLcd, int rowsLcd, int colsLcd, int pinBtn, int pinPot, SmartLightingTask* smartLight){
  this->pinLedG = pinLedG;
  this->pinLedR = pinLedR;
  this->pinTrigSonar = pinTrigSonar;
  this->pinEchoSonar = pinEchoSonar;
  this->pinMotor = pinMotor;
  this->addrLcd = addrLcd;
  this->colsLcd = colsLcd;
  this->rowsLcd = rowsLcd;
  this->pinBtn = pinBtn;
  this->pinPot = pinPot;
  this->smartLight = smartLight;
}
  
void WaterLevelTask::init(int period){
  Task::init(period);
  ledG = new Led(pinLedG);
  ledR = new Led(pinLedR);
  sonar = new SonarImpl(pinTrigSonar,pinEchoSonar);
  motor = new ServoMotorImpl(pinMotor);
  lcd = new LiquidCrystal_I2C(addrLcd,colsLcd,rowsLcd);
  lcd->init();
  button = new ButtonImpl(pinBtn);
  potentiometer = new PotentiometerImpl(pinPot);
  motor->on();
  motor->setPosition(0);
  timeChangeLedR = 0;
  attachInterrupt(digitalPinToInterrupt(pinBtn), buttonHandler, RISING);
  manualControl = false;
  state = NORMAL;
}

void WaterLevelTask::tick(){
  distance = (int)(sonar->getDistance()*100);
  state = distance > WL_NORMAL ? NORMAL : distance > WL_PRE_ALARM ? PRE_ALARM : ALARM;
  if (preState == ALARM && state != ALARM){
    manualControl = false;
    smartLight->setActive(true);
    motor->setPosition(0);
  }
  if (preState != ALARM && state == ALARM){
    manualControl = false;
  }
  preState = state;
  
  switch (state){
    case NORMAL:
      Task::init(SAMPLING_NORMAL);
      ledG->switchOn();
      ledR->switchOff();
      lcd->noBacklight();
      break;
    case PRE_ALARM:
      Task::init(SAMPLING_PRE_ALARM);
      ledG->switchOn();
      blinkLedR();
      displayPreAlarm();
      break;
    case ALARM:
      Task::init(SAMPLING_ALARM);
      smartLight->setActive(false);
      ledG->switchOff();
      ledR->switchOn();
      //from 10 to 1000 instead 0 to 1023 because the voltage drop on the potentiometer never reaches perfectly 5 or 0V.
      int angle = manualControl ? map(potentiometer->getAdjustment(), 10, 1000, 0, 180) :  map(distance, WL_PRE_ALARM, WL_MAX, 0, 180);//fare macro
      motor->setPosition(angle);
      displayAlarm();
      break;
  }
}

void WaterLevelTask::blinkLedR(){
  if (millis() - timeChangeLedR >= T_BLINK_LEDR){
    ledR->switchLight();
    timeChangeLedR = millis();
  }
}

void WaterLevelTask::displayPreAlarm(){
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
      