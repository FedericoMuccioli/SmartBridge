#include <Arduino.h>
#include "Scheduler.h"
#include "SmartLightingTask.h"
#include "WaterLevelTask.h"
#include "MsgService.h"

#define BOUND 9600
#define SCHEDULER_PERIOD 100

Scheduler sched;

void setup ( )
{
  MsgService.init(BOUND);
  sched.init(SCHEDULER_PERIOD);
  SmartLightingTask* smartLight= new SmartLightingTask(7, 5, A0);
  Task* waterLevel = new WaterLevelTask(3,4,13,12,11,0x27,20,4,2,A2,smartLight);
  smartLight->init(100);
  waterLevel->init(SAMPLING_NORMAL);
  sched.addTask(smartLight);
  sched.addTask(waterLevel);
}

void loop()
{
  sched.schedule();
}