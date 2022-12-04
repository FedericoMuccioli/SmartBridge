#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__

#include "kernel/Task.h"
#include "devices/Led.h"
#include "devices/SonarImpl.h"
#include "devices/ServoMotorImpl.h"
#include <LiquidCrystal_I2C.h>
#include "devices/ButtonImpl.h"
#include "devices/PotentiometerImpl.h"
#include "SmartLightingTask.h"
#include "ManualControl.h"
#include "ManualControlTask.h"

#define SAMPLING_NORMAL 3000
#define SAMPLING_PRE_ALARM 2000
#define SAMPLING_ALARM 1000

class WaterLevelTask: public Task {

private:
  int pinLedG;
  int pinLedR;
  int pinTrigSonar;
  int pinEchoSonar;
  int pinMotor;
  int addrLcd;
  int colsLcd;
  int rowsLcd;
  
  Light* ledG;
  Light* ledR;
  Sonar* sonar;
  ServoMotor* motor;
  //Lcd* lcd;
  LiquidCrystal_I2C *lcd;
  Active* smartLight;
  ManualControl* manualControl;
  ManualControlTask* manualControlTask;

  enum { NORMAL, PRE_ALARM, ALARM} state;

  volatile unsigned long time;
  const float WL_NORMAL = 30;
  const float WL_PRE_ALARM = 20;
  const float WL_MAX = 10;
  const unsigned long T_BLINK_LEDR = 2000;
  unsigned long timeChangeLedR;
  int distance;
  void setNormalState();
  void setPreAlarmState();
  void setAlarmState();
  void blinkLedR();
  void displayPreAlarm();
  void displayAlarm();


public:
  WaterLevelTask(int pinLedG, int pinLedR, int pinTrigSonar, int pinEchoSonar,
     int pinMotor, int addrLcd, int rowsLcd, int colsLcd, Active* smartLight, ManualControlTask* manualControlTask, ManualControl* manualControl);
  void init(int period);
  void tick();
};

#endif

