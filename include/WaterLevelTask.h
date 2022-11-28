#ifndef __WATERLEVELTASK__
#define __WATERLEVELTASK__

#include "Task.h"
#include "Led.h"
#include "SonarImpl.h"
#include "ServoMotorImpl.h"
//#include "LcdImpl.h"
#include <LiquidCrystal_I2C.h>
#include "ButtonImpl.h"
#include "PotentiometerImpl.h"



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
  int pinBtn;
  int pinPot;
  
  Light* ledG;
  Light* ledR;
  Sonar* sonar;
  ServoMotor* motor;
  //Lcd* lcd;
  LiquidCrystal_I2C *lcd;
  Button* button;
  Potentiometer* potentiometer;

  enum { NORMAL, PRE_ALARM, ALARM} state, preState;

  volatile unsigned long time;
  const float WL_NORMAL = 30;
  const float WL_PRE_ALARM = 20;
  const float WL_MAX = 10;
  const unsigned long T_BLINK_LEDR = 2000;
  unsigned long timeChangeLedR;
  int distance;
  bool manualControl;
  void blinkLedR();
  void displayPreAlarm();
  void displayAlarm();


public:
  WaterLevelTask(int pinLedG, int pinLedR, int pinTrigSonar, int pinEchoSonar, int pinMotor, int addrLcd, int rowsLcd, int colsLcd, int pinBtn, int pinPot);
  void init(int period);
  void tick();
};

#endif

