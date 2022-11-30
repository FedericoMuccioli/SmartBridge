#include <Arduino.h>
#include "SonarImpl.h"

const float soundSpeed = 331.45 + 0.62*20; //supponendo di eseguire il test in un ambiente a 20 °C

SonarImpl::SonarImpl(int trigPin, int echoPin){
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

float SonarImpl::getDistance(){
  sendImpulse();
  float distance = getTimeImpulse()*soundSpeed;
  /*debug
  Serial.print("distance: ");
  Serial.println(distance);
  */
  return distance;
}

void SonarImpl::sendImpulse(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin,LOW);
}

float SonarImpl::getTimeImpulse(){
  float tUS = pulseIn(echoPin, HIGH);
  return tUS / 1000.0 / 1000.0 / 2;
}


