
void RTCsetup()  {
  // set the Time library to use Teensy 3.0's RTC to keep time

  if (timeStatus()!= timeSet) {
      //RTC not syncing
  } else {
      //RTC synced
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

time_t ttime( int h , int min , int sec , int d , int mon , int y ){
    struct tm t;
    time_t t_of_day;
    t.tm_year = y - 1900;  // Year - 1900
    t.tm_mon = mon ;           // Month, where 0 = jan
    t.tm_mday = d ;          // Day of the month
    t.tm_hour = h ;
    t.tm_min = min ;
    t.tm_sec = sec;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);
    return (t_of_day);
}

void setTimeGps()
{
    gpsGetTime( &gpsSecond , &gpsMinute, &gpsHour , &gpsDay, &gpsMonth , &gpsYear , &dateValid , &timeValid);        
    time_t t = ttime( gpsHour , gpsMinute , gpsSecond , gpsDay , gpsMonth , gpsYear); 

    Teensy3Clock.set(t); // set the RTC
    setTime(t);

    return ;
}

void setTime_td( int h , int m , int s , int d , int month_ , int year_ ){
    //setTime(hours, minutes, seconds, days, months, years);
    time_t t = ttime( h , m , s , d , month_ , year_); 
    
    Teensy3Clock.set(t); // set the RTC
    setTime(t);
}

void setTime_td( int h , int m , int s ){
    //setTime(hours, minutes, seconds, days, months, years);
    time_t t = ttime( h , m , s ,  day() , month() , year());
    Teensy3Clock.set(t); // set the RTC
    setTime(t);
}
int RTCday(){
    return(day());
}
int RTCmonth(){
    return( month());
}
int RTCyear(){
    return(year()); 
}
int RTCseconds(){
    return(second());
}
int RTChour(){
    return(hour());
}
int RTCminute(){
    return(minute());
}
