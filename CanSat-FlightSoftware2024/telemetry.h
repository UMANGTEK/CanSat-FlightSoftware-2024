#include <string>
#include "returnstring.h"

//TEAM_ID, MISSION_TIME, PACKET_COUNT, MODE, STATE, ALTITUDE,
//AIR_SPEED, HS_DEPLOYED, PC_DEPLOYED, TEMPERATURE, VOLTAGE,
//PRESSURE, GPS_TIME, GPS_ALTITUDE, GPS_LATITUDE, GPS_LONGITUDE,
//GPS_SATS, TILT_X, TILT_Y, ROT_Z, CMD_ECHO [,,OPTIONAL_DATA]


#define TEAM_ID 2027
#define packetLength 6
#define altitudeLen 5
#define tempLen 5
#define pressLen 5
#define altiLen 7
#define latiLen 9
#define longiLen 9
#define satLen 2
#define tiltLen 7
#define voltlen 4

String str_states[] = { 
    "      LAUNCH_WAIT", 
    "           ASCENT",
    "ROCKET_SEPARATION",
    "          DESCENT",
    "      HS_RELEASED",
    "           LANDED"
};
String str_modes[] = { "F" , "S" };

String makeTelemetryPacket()
{
    String MISSION_TIME = printTime(RTChour() ,RTCminute() , RTCseconds(), RTCvalid());
    String PACKET_COUNT = printInt(packet_count, packetLength, true); 
    String ALTITUDE = printFloat(adjusted_alt, altitudeLen, 1,pressureValid);
    String TEMPERATURE = printFloat(temprature, tempLen, 1,bmpValid);
    String VOLTAGE = printFloat(voltage, voltlen, 2, true);     
    String PRESSURE = printFloat(adjusted_pressure, pressLen, 1, pressureValid);
    String GPS_TIME = printTime( gpsHour ,gpsMinute, gpsSecond, timeValid);
    String GPS_ALTITUDE = printFloat(gpsAltitude, altiLen, 1, gpsValid);
    String GPS_LATITUDE = printFloat(lat, latiLen, 6, gpsValid);
    String GPS_LONGITUDE = printFloat(lng, longiLen, 6, gpsValid);
    String GPS_SATS = printInt(noSats, satLen, satsValid);
    String TILT_X = printFloat(zAngle, tiltLen, 2, bnoValid);
    String TILT_Y = printFloat(yAngle, tiltLen, 2, bnoValid);
    String ROT_Z = printFloat(xAngle, 5, 1, bnoValid);
    String AIR_SPEED = printFloat(finalAirSpeed, 5, 1, speedValid);
    String comma = ",";

    String packet = TEAM_ID;
    packet += comma + MISSION_TIME + comma + PACKET_COUNT + comma + str_modes[currentMode] + comma + str_states[currentState]+ comma + ALTITUDE + comma + AIR_SPEED +comma + (NOSE_RELEASED?"P":"N") + comma + (PARA_DEPLOYED?"C":"N") + comma + TEMPERATURE + comma + VOLTAGE + comma + PRESSURE  + comma + GPS_TIME + comma + GPS_ALTITUDE + comma + GPS_LATITUDE + comma + GPS_LONGITUDE + comma + GPS_SATS + comma + TILT_X + comma + TILT_Y + comma + ROT_Z + comma + CMD_ECHO;
    CMD_ECHO = " " ;
    return packet;
}
