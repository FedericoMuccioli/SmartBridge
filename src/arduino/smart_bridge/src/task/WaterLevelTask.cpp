#include <Arduino.h>
#include "config.h"
#include "WaterLevelTask.h"
#include "kernel/MsgService.h"
#include "devices/Led.h"
#include "devices/SonarImpl.h"
#include "devices/ServoMotorImpl.h"
#include "devices/ButtonImpl.h"
#include "devices/PotentiometerImpl.h"

#define LEDR_BLINK_TIME 2000
#define IS_NORMAL (level < PRE_ALARM_WL)
#define IS_PRE_ALARM (level >= PRE_ALARM_WL && level < ALARM_WL)
#define IS_ALARM (level >= ALARM_WL)
#define AUTOMATIC_CONTROL_VALUE map(level, ALARM_WL, MAX_WL, 0, 180)
#define MSG(state) (state == NORMAL ? String("NORMAL") : state == PRE_ALARM ? String("PRE ALARM") : String("ALARM"))

WaterLevelTask::WaterLevelTask(Active* smartLightTask, Active* manualControlTask, ManualControl* manualControl){
  this->smartLightTask = smartLightTask;
  this->manualControl = manualControl;
  this->manualControlTask = manualControlTask;
  ledG = new Led(LED_G_PIN);
  ledR = new Led(LED_R_PIN);
  sonar = new SonarImpl(TRIG_SONAR_PIN,ECHO_SONAR_PIN);
  motor = new ServoMotorImpl(MOTOR_PIN);
  lcd = new LiquidCrystal_I2C(ADDR_LCD,COLS_LCD,ROWS_LCD);
}
  
void WaterLevelTask::init(int period){
  Task::init(period);
  lcd->init();
  motor->on();
  motor->setPosition(0);
  smartLightTask->setActive(true);
  manualControlTask->setActive(false);
  setNormalState();
}

void WaterLevelTask::tick(){
  level = DIST_SONAR_FROM_BOT - sonar->getDistance()*100;
  level = level < 0 ? 0 : level;
  switch (state){
    case NORMAL:
      if (IS_PRE_ALARM){
        setPreAlarmState();
      } else if (IS_ALARM){
        setAlarmState();
      }
      break;

    case PRE_ALARM:
      if(IS_NORMAL){
        setNormalState();
      } else if(IS_ALARM){
        setAlarmState();
      } else {
        blinkLedR();
        displayPreAlarm();
      }
      break;

    case ALARM:
      if (level < ALARM_WL){
        motor->setPosition(0);
        smartLightTask->setActive(true);
        manualControlTask->setActive(false);
        if(IS_NORMAL){
          setNormalState();
        } else if (IS_PRE_ALARM){
          setPreAlarmState();
        }
      } else {
        int angle = manualControl->isActive() ? manualControl->getValue() :  AUTOMATIC_CONTROL_VALUE;
        motor->setPosition(angle);
        displayAlarm();
      }
      break;
  }
  MsgService.sendMsg(WATER_LEVEL_STATE_MSG + MSG(state));
  MsgService.sendMsg(WATER_LEVEL_MSG + String(level));
}

void WaterLevelTask::setNormalState(){
  ledG->switchOn();
  ledR->switchOff();
  lcd->noBacklight();
  Task::init(NORMAL_PERIOD);
  state = NORMAL;
}

void WaterLevelTask::setPreAlarmState(){
  timeChangeLedR = 0;
  ledG->switchOn();
  blinkLedR();
  displayPreAlarm();
  Task::init(PRE_ALARM_PERIOD);
  state = PRE_ALARM;
}

void WaterLevelTask::setAlarmState(){
  ledR->switchOn();
  ledG->switchOff();
  smartLightTask->setActive(false);
  manualControlTask->setActive(true);
  int angle = manualControl->isActive() ? manualControl->getValue() :  AUTOMATIC_CONTROL_VALUE;
  motor->setPosition(angle);
  displayAlarm();
  Task::init(ALARM_PERIOD);
  state = ALARM;
}

void WaterLevelTask::blinkLedR(){
  if (millis() - timeChangeLedR >= LEDR_BLINK_TIME){
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
  lcd->print(level);
}

void WaterLevelTask::displayAlarm(){
  lcd->backlight();
  lcd->clear();
  lcd->print("ALARM");
  lcd->setCursor(0,2);
  lcd->print("Water Level: ");
  lcd->print(level);
  lcd->setCursor(0,3);
  lcd->print("Valve degrees: ");
  lcd->print(motor->getPosition());
}
      