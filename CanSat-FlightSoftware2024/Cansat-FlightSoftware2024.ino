#define packetTimePeriod 1000
#include <TimeLib.h>

#include "servo.h"
#include "eeprom_rw.h"
#include "led_buzzer.h"
#include "telemetry.h"
#include "smartDelay.h"

enum states {
  IDLE ,
  LAUNCH_WAIT ,
  ASCENT ,
  DECENT ,
  PARA_NOSECONE_DEPLOYED ,
  LANDED
};
enum modes {
  FLIGHT,
  SIMULATION
};

int currentState = IDLE ;
int currentMode = FLIGHT ;
int packet_count = 0;
bool PARA_deployed = false;
bool NOSE_RELEASED = false;


void setup()
{
}

void loop()
{
}
