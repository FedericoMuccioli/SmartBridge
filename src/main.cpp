#include <Arduino.h>
#include "SmartLightingTask.h"
/*
#include "Led.h"
#include "LightSensorImpl.h"
#include "PirSensorImpl.h"*/
#include "ButtonImpl.h"
#include "PotentiometerImpl.h"
#include "ServoMotorImpl.h"
#include "SonarImpl.h"
#include "LcdImpl.h"

SmartLightingTask* smartLightingTask;
/*
Light* light;
LightSensor* lightSensor;
PirSensor* pirSensor;*/
Button* button;
Potentiometer* potentiometer;
ServoMotor* motor;
Sonar* sonar;
Lcd* lcd;
 


void setup ( )
{
  Serial.begin(9600);
  smartLightingTask = new SmartLightingTask(2, 5, A0);
  smartLightingTask->init(0);
  /*
  light = new Led(LED_BUILTIN);
  lightSensor = new LightSensorImpl(A0);
  pirSensor = new PirSensorImpl(5);*/
  button = new ButtonImpl(7);
  potentiometer = new PotentiometerImpl(A2);
  motor = new ServoMotorImpl(11);
  sonar = new SonarImpl(13, 12);
  lcd = new LcdImpl(0x27,20,4);
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

  smartLightingTask->tick();

  
  


  /*POTREI METTERLE NEL DEBUG
  Serial.print(pot);
  Serial.print(" ");
  Serial.println(val);
  */
  

}