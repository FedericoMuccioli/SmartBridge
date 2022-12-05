#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__

#include "kernel/Active.h"
#include "kernel/Task.h"
#include "devices/Light.h"
#include "ManualControl.h"
#include "devices/Sonar.h"
#include "devices/ServoMotor.h"
#include <LiquidCrystal_I2C.h>
#include "devices/Button.h"
#include "devices/Potentiometer.h"

#define NORMAL_PERIOD 3000
#define PRE_ALARM_PERIOD 2000
#define ALARM_PERIOD 1000

class WaterLevelTask: public Task {

private:
  Active* smartLight;
  Active* manualControlTask;
  ManualControl* manualControl;
  Light* ledG;
  Light* ledR;
  Sonar* sonar;
  ServoMotor* motor;
  //Lcd* lcd;
  LiquidCrystal_I2C *lcd;
  enum { NORMAL, PRE_ALARM, ALARM} state;
  unsigned long timeChangeLedR;
  int distance;
  void setNormalState();
  void setPreAlarmState();
  void setAlarmState();
  void blinkLedR();
  void displayPreAlarm();
  void displayAlarm();

public:
  WaterLevelTask(Active* smartLight, Active* manualControlTask, ManualControl* manualControl);
  void init(int period);
  void tick();
};

#endif

