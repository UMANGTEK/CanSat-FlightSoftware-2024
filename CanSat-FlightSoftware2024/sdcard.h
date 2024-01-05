#include <SD.h>
#include <SPI.h>

File telemetryFile;
File logFile;

void SDsetup()
{
    if (!SD.begin(BUILTIN_SDCARD)) {
        //failed
        Serial.println("failure");
        SD_works = false;
        return;
    }
    SD_works = true ;
}
void failedWrite (){
    // Runs when writing to Sd card fails
    SD_works = false;
    Serial.println("failure write");
}
void saveTelemetryInSdCard( String telemetryString )
{
    // if the file opened okay, write to it:
   if ( !SD_works ){
        return;
    }
    telemetryFile = SD.open("telemetry.csv", FILE_WRITE);
    if (telemetryFile) {
        telemetryFile.println(telemetryString);
        telemetryFile.close();
        Serial.println("success");
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
