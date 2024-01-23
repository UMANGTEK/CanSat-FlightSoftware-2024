Q#define packetTimePeriod 1000

String comm = "sad";

enum states {
  IDLE ,
  LAUNCH_WAIT ,
  ASCENT ,
  ROCKET_SEPARATION,
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
bool PARA_DEPLOYED = false;
bool NOSE_RELEASED = false;

float zero_alt_calib = 0;
bool telemetry = true;
bool tilt_calibration = false ;
bool simulation_enabled = false;

String CMD_ECHO = "";
float voltage = 0;

float temprature = 0 , altitude = 0 , pressure = 0 ;
bool bmpValid = false ;

float xAngle = 0 , yAngle = 0 , zAngle = 0 , acceleration = 0 ;
bool bnoValid = false ;

float noSats = 0 , lat = 0 , lng = 0 , gpsAltitude = 0 ;
bool satsValid = false, locValid = false, altValid = false;

int gpsSecond = 0 , gpsMinute = 0 , gpsHour = 0  , gpsDay = 0 , gpsMonth = 0, gpsYear = 0 ;
bool timeValid = false , dateValid = false ;

float adjusted_alt= 0 ;
float adjusted_pressure= 0 ;
bool pressureValid = false ;
bool SD_works = false;

#include "servo.h"
//#include "reset.h"
//#include "sdcard.h"
#include "led_buzzer.h"
#include "./sensors/battery.h"
#include "./sensors/gpssensor.h"
#include "RTCtime.h"
#include "checkheight.h"
#include "eeprom_rw.h"
#include "telemetry.h"
#include "./sensors/bmpsensor.h"
//#include "xbeeComms.h"
#include "./sensors/bnosensor.h"
#include "smartDelay.h"
#include "cmdProcessing.h"

void setup()
{
  currentState = EEreadInt(1);
  currentMode = EEreadInt(2);
  packet_count = EEreadInt(3);
  zero_alt_calib = EEreadFloat(4);
  NOSE_RELEASED = EEreadInt(5);
  PARA_DEPLOYED = EEreadInt(6);
  Serial.begin(9600);
  led_buzzer_Setup();
  //setSyncProvider(getTeensy3Time);
  //resetSetup();
  //SDsetup();
  bnoSetup();
  bmpSetup();
  gpsSetup();
  //xbeeSetup();
  //cameraSetup();
  servoSetup();
  //RTCsetup();

  lockPrachute();
  lockNoseCone();
}

void loop(){
  
   if ( bmpValid && bnoValid && timeValid && dateValid && satsValid && locValid && altValid ){
    greenON();
    }
  else{
    greenOFF();
    } 

  switch (currentState){ 
    case IDLE:
      if (tilt_calibration) {
        int tilt_cal_status = bnoCalibration();
        //sendDataTelemetry(String("Tilt Calibration: ") + String(tilt_cal_status) + String("|"));
        if ( !tilt_cal_status ) {
          tilt_calibration = false;
        }
      }
      break;
      
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
      if ( movingDown() ) {
        currentState = DECENT;
      }
      else if(notMoving()){
        currentState = ROCKET_SEPARATION;
      }
      break;
    case ROCKET_SEPARATION:
      if(movingDown()){
        currentState = DECENT;
      }
      break;
    case DECENT:
      // Check if altitude is less than 100m if yes change state to payload_separated
      if ( checkAlt(100) ) {
        currentState = PARA_NOSECONE_DEPLOYED;
        deployNoseCone();
        deployParachute();
      }
      break;
    case PARA_NOSECONE_DEPLOYED:
      if(notMoving()){
        currentState = LANDED;
      }
      break;
   
    case LANDED:
     
      break;
    default:
      break;
     }
     
     if (Serial.available())
      comm = Serial.readString();
     packetCheck(comm);
     comm = "asdas";
     
     smartDelay();
}
