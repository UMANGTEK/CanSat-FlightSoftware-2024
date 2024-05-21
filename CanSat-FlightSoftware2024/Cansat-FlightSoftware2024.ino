#define packetTimePeriod 500
#define MS_100 100
#define SEPARATION_ERR 30
#define LANDED_ERR 2
#include <Arduino.h>
#include "TeensyThreads.h"

String comm = "GARBAGE";
String packetRecieved = "GARBAGE";

enum states {
  LAUNCH_WAIT,
  ASCENT,
  ROCKET_SEPARATION,
  DECENT,
  HS_RELEASED,
  LANDED
};
enum modes {
  FLIGHT,
  SIMULATION
};

int currentState = LAUNCH_WAIT ;
int currentMode = FLIGHT ;
int packet_count = 0;
int BCN = false;
bool PARA_DEPLOYED = false;
bool NOSE_RELEASED = false;

bool simFlag = 0;
float zero_alt_calib = 0;
bool telemetry = true;
bool tilt_calibration = false ;
bool simulation_enabled = false;

String CMD_ECHO = "";
float voltage = 0;

float temprature = 0 , altitude = 0 , pressure = 0, prevAlt = 0, bmpSpeed = 0 ;
bool bmpValid = false ;

float xAngle = 0 , yAngle = 0 , zAngle = 0 , acceleration = 0 ;
bool bnoValid = false ;

float noSats = 0 , lat = 0 , lng = 0 , gpsAltitude = 0 , gpsSpeed = 0 ;
bool gpsValid = false, satsValid = true;

int gpsSecond = 0 , gpsMinute = 0 , gpsHour = 0  , gpsDay = 0 , gpsMonth = 0, gpsYear = 0 ;
bool timeValid = false , dateValid = false ;

float filterPitotVelocity = 0;
float pitotCalibRestValue = 8192.0;  //CombinedDec at rest 
float dt = 0.1;
float process_noise = 5; //Error by prediction model
float measurement_noise = 1;  //Error by sensor
float pitotSpeedConstant = 0.3; //(0-1)
float finalAirSpeed = 0;
bool speedValid = false;
bool pitotValid = false;

float adjusted_alt = 0 ;
float adjusted_pressure = 0 ;
bool pressureValid = false ;
bool SD_works = false;

#include "servo.h"
#include "sdcard.h"
#include "led_buzzer.h"
#include "./sensors/battery.h"
#include "./sensors/gpssensor.h"
#include "RTCtime.h"
#include "checkheight.h"
#include "eeprom_rw.h"
#include "telemetry.h"
#include "./sensors/bmpsensor.h"
#include "xbeeComms.h"
#include "./sensors/bnosensor.h"
#include "./sensors/pitot_tube.h"
#include "cmdProcessing.h"
#include "airspeed.h"
#include "smartDelay.h"

void setup()
{
  led_buzzer_Setup();
  redON();
  currentState = EEreadInt(1);
  currentMode = EEreadInt(2);
  packet_count = EEreadInt(3);
  zero_alt_calib = EEreadFloat(4);
  NOSE_RELEASED = EEreadInt(5);
  PARA_DEPLOYED = EEreadInt(6);
  BCN = EEreadInt(7);
  simFlag = EEreadInt(8);
  pitotCalibRestValue = EEreadFloat(9);
  Serial.begin(9600);
  SDsetup();
  pitotSetup();
  bnoSetup();
  bmpSetup();
  //gpsSetup();
  xbeeSetup();
  servoSetup();

  BCN ? buzzerON() : buzzerOFF();
  NOSE_RELEASED ? deployNoseCone() : lockNoseCone();
  PARA_DEPLOYED ? deployParachute() : lockPrachute();
  threads.addThread(updateGPS);
}

void loop() {
   
   if (bmpValid && bnoValid && timeValid && satsValid && gpsValid && RTCvalid() && pitotValid)
  {
    greenON();
  }
  else if (bmpValid && bnoValid && RTCvalid() && pitotValid)
  {
    blink(greenLED, 500);
  }
  else
  {
    greenOFF();
  }


  switch (currentState) {
    case LAUNCH_WAIT:
      // check if cansat has started accending if yes change state
      if ( movingUp() ) {
        currentState = ASCENT;
      }
      else if ( movingDown() ) {
        currentState = DECENT;
      }

      break;

    case ASCENT:
      // check if cansat has stopped accent and started going downwards ( decreasing altitude)
      if (notMoving(SEPARATION_ERR) ) {
        currentState = ROCKET_SEPARATION;
      }
      else if (movingDown()) {
        currentState = DECENT;
      }
      break;

    case ROCKET_SEPARATION:
      if (movingDown()) {
        currentState = DECENT;
      }
      break;

    case DECENT:
      bmpGetValues();
      if (currentMode == FLIGHT)
        updateAlt(adjusted_alt);

      // Check if altitude is less than 100m if yes change state to payload_separated
      if (checkAlt(120)) {
        deployParachute();
      }
      
      if ( checkAlt(100) ) {
        currentState = HS_RELEASED;
        PARA_DEPLOYED = true ;
        deployParachute();
        deployNoseCone();
        WriteALL();
      }
      break;

    case HS_RELEASED:
      if (notMoving(LANDED_ERR)) {
        currentState = LANDED;
      }
      break;

    case LANDED:
      buzzerON();
      break;

    default:
      break;
  }

  if (Serial.available()) {
    comm = Serial.readString();
    packetCheck(comm);
    comm = "GARBAGE_VALUE";
  }
  
    recieveDataTelemetry();
    packetCheck(packetRecieved);
    packetRecieved = "GARBAGE_VALUE";
 
  
  smartDelay();
}
