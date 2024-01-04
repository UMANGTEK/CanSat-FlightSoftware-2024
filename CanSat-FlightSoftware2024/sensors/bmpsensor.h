#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP3XX bmp;

int bmpSetup(){
  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
    //Failed to connect
    return(1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  return(0);
}


void bmpGetValues(){
  if (! bmp.performReading()) {
    //Failed to read DATA
    bmpValid=false;
    if ( currentMode == FLIGHT){
      pressureValid = false ;
    }
  }
  else{
    bmpValid = true;
    temprature = bmp.temperature;
    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA) ;
    pressure = bmp.pressure / 100.0;
    if ( currentMode == FLIGHT ) {
      adjusted_alt = altitude - zero_alt_calib;
      adjusted_pressure = pressure;
      pressureValid = bmpValid;
    }
  }
}
