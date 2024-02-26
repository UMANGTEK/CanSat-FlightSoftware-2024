#include <SD.h>
#define blueLED 4

const int chipSelect = BUILTIN_SDCARD;

File telemetryFile;
File logFile;

void SDsetup()
{
    if (!SD.begin(chipSelect)) {
        //failed
        //blueOFF();
        digitalWrite(blueLED,LOW);
        Serial.println("failure");
        SD_works = false;
        return;
    }
    SD_works = true ;
}
void failedWrite (){
    // Runs when writing to Sd card fails
    SD_works = false;
}
void saveTelemetryInSdCard( String telemetryString )
{
    // if the file opened okay, write to it:
   if ( SD_works == true){
    if(!SD.begin(chipSelect))
      {
        digitalWrite(blueLED,LOW);
        SD_works = false;
        return; 
      }
    }
    else
      return;
      
    telemetryFile = SD.open("telemetry.csv", FILE_WRITE);
    if (telemetryFile) {
        telemetryFile.println(telemetryString);
        telemetryFile.close();
        //blueON();
        digitalWrite(blueLED,HIGH);
        SD_works = true;
    } else {
        // Failed to write to file
        failedWrite();
    }
}

void log( String logdata ){
    if ( !SD_works ){
        return;
    }
    logFile = SD.open("logs.txt", FILE_WRITE);
    if (logFile) {
        logFile.println(logdata);
        logFile.close();
    } else {
        // Failed to write to file
        failedWrite();
    }
}
