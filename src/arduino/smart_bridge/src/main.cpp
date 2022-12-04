#include <Arduino.h>
#include "kernel/Scheduler.h"
#include "task/SmartLightingTask.h"
#include "task/WaterLevelTask.h"
#include "kernel/MsgService.h"
#include "SmartLighting.h"
#include "task/ManualControlTask.h"
#include "ManualControl.h"

#define BOUND 9600
#define SCHEDULER_PERIOD 100

Scheduler sched;
SmartLighting* smartLighting;
ManualControl* manualControl;

void setup ( )
{
  sched.init(SCHEDULER_PERIOD);
  MsgService.init(BOUND);
  
  smartLighting = new SmartLighting();
  manualControl = new ManualControl();


  Task* smartLightingTask= new SmartLightingTask(smartLighting);
  ManualControlTask* manualControlTask = new ManualControlTask(manualControl);
  Task* waterLevelTask = new WaterLevelTask(3,4,13,12,11,0x27,20,4,smartLightingTask, manualControlTask, manualControl);
  
  manualControlTask->init(200);
  smartLightingTask->init(100);
  waterLevelTask->init(SAMPLING_NORMAL);
  sched.addTask(manualControlTask);//ris
  sched.addTask(smartLightingTask);
  sched.addTask(waterLevelTask);
}

void loop()
{
  sched.schedule();
}