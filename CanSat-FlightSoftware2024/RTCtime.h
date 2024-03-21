#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

tmElements_t tm;

bool RTCvalid()
{
  return RTC.read(tm);
}

void getRTCTime()
{
  RTC.read(tm);
  return ;
}


void setTimeGps()
{
    //gpsGetTime( &gpsSecond , &gpsMinute, &gpsHour , &gpsDay, &gpsMonth , &gpsYear , &dateValid , &timeValid);        
   // updateGPS();
    tm.Hour = gpsHour;
    tm.Minute = gpsMinute;
    tm.Second = gpsSecond;
    tm.Day = gpsDay;
    tm.Month = gpsMonth;
    tm.Year = gpsYear;
    
    RTC.write(tm); // set the RTC
    return ;
}

void setTime_td( int h , int m , int s , int d , int month_ , int year_ ){
    //setTime(hours, minutes, seconds, days, months, years);
    tm.Hour = h;
    tm.Minute = m;
    tm.Second = s;
    tm.Day = d;
    tm.Month = month_;
    tm.Year = year_;
    
    RTC.write(tm); // set the RTC
}

void setTime_td( int h , int m , int s ){
     //setTime(hours, minutes, seconds);
    tm.Hour = h;
    tm.Minute = m;
    tm.Second = s;
    
    RTC.write(tm); // set the RTC
}
int RTCday(){
    RTC.read(tm);
    return(tm.Day);
}
int RTCmonth(){
    RTC.read(tm);
    return(tm.Month);
}
int RTCyear(){
    RTC.read(tm);
    return(tm.Month); 
}
int RTCseconds(){
    RTC.read(tm);
    return(tm.Second);
}
int RTChour(){
    RTC.read(tm);
    return(tm.Hour);
}
int RTCminute(){
    RTC.read(tm);
    return(tm.Minute);
}
