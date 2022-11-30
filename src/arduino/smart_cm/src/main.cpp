#include <Arduino.h>
#include "Scheduler.h"
#include "SmartLightingTask.h"
#include "WaterLevelTask.h"
#include "MsgService.h"

#define BOUND 9600
/*
#include "Led.h"
#include "LightSensorImpl.h"
#include "PirSensorImpl.h"
#include "ServoMotorImpl.h"
#include "SonarImpl.h"
#include "LcdImpl.h"
#include "ButtonImpl.h"
#include "PotentiometerImpl.h"
*/

Scheduler sched;
/*
SmartLightingTask* smartLightingTask;
WaterLevelTask* waterLevelTask;
Light* light;
LightSensor* lightSensor;
PirSensor* pirSensor;
ServoMotor* motor;
Sonar* sonar;
Lcd* lcd;
Button* button;
Potentiometer* potentiometer;
*/


void setup ( )
{
  MsgService.init(BOUND);
  sched.init(100);
  SmartLightingTask* smartLight= new SmartLightingTask(7, 5, A0);
  Task* waterLevel = new WaterLevelTask(3,4,13,12,11,0x27,20,4,2,A2,smartLight);
  smartLight->init(100);
  waterLevel->init(SAMPLING_NORMAL);
  sched.addTask(smartLight);
  sched.addTask(waterLevel);

  //smartLightingTask = new SmartLightingTask(7, 5, A0);
  //smartLightingTask->init(0);
  //waterLevelTask = new WaterLevelTask(3,4,13,12,11,0x27,20,4,2,A2);
  //waterLevelTask->init(0);
  /*
  light = new Led(7);
  lightSensor = new LightSensorImpl(A0);
  pirSensor = new PirSensorImpl(5);
  motor = new ServoMotorImpl(11);
  sonar = new SonarImpl(13, 12);
  lcd = new LcdImpl(0x27,20,4);
  button = new ButtonImpl(2);
  potentiometer = new PotentiometerImpl(A2);
  */
  
  
}

void loop()
{
  /*
  light->switchOn();
  delay(500);
  light->switchOff();
  delay(500);
  lightSensor->getLightIntensity();
  pirSensor->isMoved();
  button->isPressed();
  potentiometer->getAdjustment();
  int val = map(pot > 1012 ? 1012 : pot, 0, 1012, 0, 180); //1012 instead 1023 because the voltage drop on the potentiometer never reaches 5v
  motor->on();
  motor->off();
  motor->setPosition(180);
  sonar->getDistance();
  lcd->setCursor(0, 0); // Set the cursor on the third column and first row.
  lcd->print("Ciao");
  */

  //smartLightingTask->tick();
  //waterLevelTask->tick();
  //delay(1000);
  sched.schedule();
  


  /*POTREI METTERLE NEL DEBUG
  Serial.print(pot);
  Serial.print(" ");
  Serial.println(val);
  */
  

}