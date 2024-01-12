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
    if ( currentMode == FLIGHT){
      pressureValid = false ;
    }
  }
  else{
    bmpValid = true;
    temprature = bmp.readTemperature();
    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA) ;
    pressure = bmp.readPressure() / 100.0;
    if ( currentMode == FLIGHT ) {
      adjusted_alt = altitude - zero_alt_calib;
      adjusted_pressure = pressure;
      pressureValid = bmpValid;
    }
  }
}
