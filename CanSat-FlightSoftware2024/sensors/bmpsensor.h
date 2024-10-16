#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP280 bmp;

int bmpSetup(){
  if (!bmp.begin(0x76)) {   // hardware I2C mode, can pass in address & alt Wire
    //Failed to connect
    return(1);
  }

  // Set up oversampling and filter initialization
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  return(0);
}


void bmpGetValues(){
  if (!bmp.begin(0x76)) {
    //Failed to read DATA
    bmpValid=false;
    if(gpsValid){
    altitude= gpsAltitude;
    altitudeValid= true;
    }else{
      altitudeValid= false;
    }
    if ( currentMode == FLIGHT){
      pressureValid = false ;
      if(gpsValid){
      gpsAltitude= gpsAltitude-refgpsAltitude;
      adjusted_altitude= gpsAltitude;
      altitudeValid= true;
      }else{
      altitudeValid= false;
      }
    }
  }
  else
  {
    bmpValid = true;
    temprature = bmp.readTemperature();
    if(gpsValid){
    bmpAltitude = bmp.readAltitude(SEALEVELPRESSURE_HPA) ;
    altitude= (bmpAltitude+gpsAltitude)/2;
    altitudeValid= true;
    }else{
      bmpAltitude = bmp.readAltitude(SEALEVELPRESSURE_HPA) ;
      altitude= bmpAltitude;
      altitudeValid= true;
    }
    pressure = bmp.readPressure() / 1000.0;
    if ( currentMode == FLIGHT ) {
      if(gpsValid){
      gpsAltitude= gpsAltitude-refgpsAltitude;
      bmp_adjusted_alt = bmpAltitude - zero_alt_calib;
      adjusted_alt= (bmp_adjusted_alt+gpsAltitude)/2
      altitudeValid= true;
      }else{
        bmp_adjusted_alt = bmpAltitude - zero_alt_calib;
        adjusted_alt= bmp_adjusted_alt;
        altitudeValid= true;
      }
      adjusted_pressure = pressure;
      pressureValid = bmpValid;
    }
  }
}
