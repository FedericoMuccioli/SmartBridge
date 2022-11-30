#include <Arduino.h>
#include "ManualControl.h"
#include "config.h"

bool manualControl = false;
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
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonHandler, RISING);
}

void ManualControl::endCheck(){
  detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
}

bool ManualControl::isActive(){
  return manualControl;
}

int ManualControl::getValue(){
  return potentiometer->getAdjustment();
}
