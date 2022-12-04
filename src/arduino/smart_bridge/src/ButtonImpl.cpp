#include <Arduino.h>
#include "ButtonImpl.h"

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);     
} 
  
bool ButtonImpl::isPressed(){
  bool var =digitalRead(pin);
  if(var == HIGH){
    Serial.println("pressed");
  }
  return var == HIGH;
}


