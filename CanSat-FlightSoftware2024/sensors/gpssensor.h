#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#define GPS_SoftwareSerial Serial5
//SoftwareSerial GPS_SoftwareSerial(35, 34); // RX, TX (connect your GPS module's TX pin to Teensy pin 3, and RX pin to Teensy pin 2)
Adafruit_GPS GPS(&GPS_SoftwareSerial);

String NMEA1;
String NMEA2;
char c;

void updateGPS() {
  //setup
  GPS_SoftwareSerial.begin(9600);  // Initialize SoftwareSerial at 9600 baud
  GPS.begin(9600);       // Turn GPS on at baud rate of 9600
  GPS.sendCommand("$PGCMD,33,0*6D"); // Turn Off GPS Antenna Update or remove it to use an Antenna
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Tell GPS we want only $GPRMC and $GPGGA NMEA sentences if raw data change it to ALLDATA
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate or use 5HZ, 10HZ
  threads.delay(500);
  //readGPS();
  //clearGPS();

  while(1){
    unsigned long enterMillis = millis();  
  while (!GPS.newNMEAreceived()) {
    unsigned long currentMillis = millis();
    if(currentMillis - enterMillis >1000)
      break;
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

  enterMillis = millis();
  while (!GPS.newNMEAreceived()) {
     unsigned long currentMillis = millis();
    if(currentMillis - enterMillis >1000)
      break;
    c = GPS.read();
  }
  GPS.parse(GPS.lastNMEA());

  
  //while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  //}
  GPS.parse(GPS.lastNMEA());
  NMEA1 = GPS.lastNMEA();

  //while (!GPS.newNMEAreceived()) {
    c = GPS.read();
  //}
  GPS.parse(GPS.lastNMEA());
  NMEA2 = GPS.lastNMEA();

  gpsHour = GPS.hour;
  gpsMinute = GPS.minute;
  gpsSecond = GPS.seconds;

  gpsDay = GPS.day;
  gpsMonth = GPS.month;
  gpsYear = GPS.year;
  
  if(gpsDay!=0 && gpsMonth!=0 && gpsYear!=0)
    timeValid = true;
  else
    timeValid = false;
  gpsValid = GPS.fix;
  noSats = GPS.satellites;

  gpsAltitude = GPS.altitude;
  lat = GPS.latitudeDegrees;
  lng = GPS.longitudeDegrees;
  gpsSpeed = GPS.speed;
  }
  

  // if (GPS.fix==1) {
  //   Serial.print("Location: ");
  //   Serial.print(GPS.latitude, 4);
  //   Serial.print(GPS.lat);
  //   Serial.print(", ");
  //   Serial.print(GPS.longitude, 4);
  //   Serial.println(GPS.lon);
  //   Serial.print("Google Maps location: ");
  //   Serial.print(GPS.latitudeDegrees, 4);
  //   Serial.print(", ");
  //   Serial.println(GPS.longitudeDegrees, 4);

  //   Serial.print("Speed (knots): ");
  //   Serial.println(GPS.speed);
  //   Serial.print("Heading: ");
  //   Serial.println(GPS.angle);
  //   Serial.print("Altitude: ");
  //   Serial.println(GPS.altitude);
  // }
  // Serial.println("-------------------------------------");
}