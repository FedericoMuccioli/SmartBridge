#ifndef __CONFIG__
#define __CONFIG__

#define BOUND 9600
#define SCHEDULER_PERIOD 100

#define DIST_SONAR_FROM_BOT 100 //cm
#define PRE_ALARM_WL 70
#define ALARM_WL 80
#define MAX_WL 90

#define SMART_LIGHTING_STATE_MSG "l"
#define WATER_LEVEL_STATE_MSG "w"
#define WATER_LEVEL_MSG "v"
#define MANUAL_CONTROL_MSG "c"

#define PHOTO_PIN A0
#define POT_PIN A2
#define PIR_PIN 5
#define LIGHT_PIN 7
#define BUTTON_PIN 2
#define LED_G_PIN 3
#define LED_R_PIN 4
#define TRIG_SONAR_PIN 13
#define ECHO_SONAR_PIN 12
#define MOTOR_PIN 11
#define ADDR_LCD 0x27
#define ROWS_LCD 20
#define COLS_LCD 4

#endif
