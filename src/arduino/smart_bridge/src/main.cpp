#include <Arduino.h>
#include "Scheduler.h"
#include "SmartLightingTask.h"
#include "WaterLevelTask.h"
#include "MsgService.h"
#include "SmartLighting.h"

#define BOUND 9600
#define SCHEDULER_PERIOD 100

Scheduler sched;
SmartLighting* smartLighting;

void setup ( )
{
  sched.init(SCHEDULER_PERIOD);
  MsgService.init(BOUND);
  
  smartLighting = new SmartLighting();

  Task* smartLightingTask= new SmartLightingTask(smartLighting);
  Task* waterLevelTask = new WaterLevelTask(3,4,13,12,11,0x27,20,4,smartLightingTask);
  smartLightingTask->init(1000);
  waterLevelTask->init(SAMPLING_NORMAL);
  sched.addTask(smartLightingTask);
  sched.addTask(waterLevelTask);
}

void loop()
{
  sched.schedule();
}