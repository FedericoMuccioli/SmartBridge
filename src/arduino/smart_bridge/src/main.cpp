#include <Arduino.h>
#include "config.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler.h"
#include "SmartLighting.h"
#include "ManualControl.h"
#include "task/SmartLightingTask.h"
#include "task/ManualControlTask.h"
#include "task/WaterLevelTask.h"

Scheduler sched;
SmartLighting* smartLighting;
ManualControl* manualControl;

void setup()
{
  sched.init(SCHEDULER_PERIOD);
  MsgService.init(BOUND);
  
  smartLighting = new SmartLighting();
  manualControl = new ManualControl();

  Task* smartLightingTask= new SmartLightingTask(smartLighting);
  Task* manualControlTask = new ManualControlTask(manualControl);
  Task* waterLevelTask = new WaterLevelTask(smartLightingTask, manualControlTask, manualControl);
  
  smartLightingTask->init(SMART_LIGHTING_PERIOD);
  manualControlTask->init(MANUAL_CONTROL_PERIOD);
  waterLevelTask->init(NORMAL_PERIOD);
  sched.addTask(manualControlTask);
  sched.addTask(smartLightingTask);
  sched.addTask(waterLevelTask);
}

void loop()
{
  sched.schedule();
}