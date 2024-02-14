#include <TinyGPSPlus.h>

TinyGPSPlus gps;
#define gpsSerial Serial2
#define gpsBaud 9600

void gpsSetup(){
  gpsSerial.begin(gpsBaud);
}
void gpsReading( float *sats , float *lat , float *lng , float *alt , bool *satsValid , bool *locValid , bool *altValid ){
  *sats =  gps.satellites.value();
  *lat =  gps.location.lat();
  *lng =  gps.location.lng();
  *alt =  gps.altitude.meters();
  *satsValid =  gps.satellites.isValid();
  *locValid =  gps.location.isValid();
  *altValid =   gps.altitude.isValid();
}

void gpsGetTime( int *second , int *minute , int *hour , int *day ,int *month , int *year , bool *timeValid ,bool *dateValid  ){
  *second = gps.time.second();
  *minute = gps.time.minute(); 
  *hour = gps.time.hour(); 
  *day = gps.date.day();
  *month = gps.date.month();
  *year = gps.date.year();
  *timeValid = gps.time.isValid();
  *dateValid = gps.date.isValid();
}

void gpsGetValues ( int *sats , bool *satsValid , float *lat , float *lng , bool *locValid , float *alt , bool *altValid ){
  *sats = gps.satellites.value();
  *satsValid = gps.satellites.isValid();
  
  *lat = gps.location.lat();
  *lng = gps.location.lng();
  *locValid = gps.location.isValid();
  
  *altValid = gps.altitude.isValid();
  *alt = gps.altitude.meters();
}

void processGps(){
    while (gpsSerial.available())
      gps.encode(gpsSerial.read());
}
