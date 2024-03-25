unsigned long previousMillis = 0;    // Stores the last time the task was executed
unsigned long previousMillis_100MS = 0;

void periodic_Task() {
   packet_count++;

  // Read Sensor Data
  //GPS data
//  gpsGetTime( &gpsSecond , &gpsMinute, &gpsHour , &gpsDay, &gpsMonth , &gpsYear , &dateValid , &timeValid);
//  gpsReading(&noSats , &lat , &lng , &gpsAltitude , &satsValid, &locValid  , &altValid );

  //updateGPS();
  
  //BNO data
  bnoGetValues();
  
  //Voltage
  readVoltage();
  
  //BMP data
  prevAlt = altitude;
  bmpGetValues();
  bmpSpeed = abs(altitude - prevAlt);
  //Pitot Data
  getPitotSpeed();

  //Get speed from Pitot and BMP 
  getAirSpeed();
  //Process recieved commmands
  //get packet
//  if ( packetAvailable() ) {
//    String packetRecieved = getOnePacket();
//    packetCheck(packetRecieved);
//  }

  if(currentMode == FLIGHT)
    updateAlt(adjusted_alt);
    
  //Make telemetry packet
  String telemetry_string = makeTelemetryPacket();

  //Transmit data to GCS over Xbee
  if ( telemetry ){
    sendDataTelemetry(telemetry_string);
    //Serial.println(telemetry_string);
  }

  //Save Data to sd card  
  saveTelemetryInSdCard(telemetry_string);

  // Save state to EEPROM
  WriteALL();
  
  if(!bnoValid)
    checkBno();
  
}

//SmartDelay for telemetry packet of 1 second
void smartDelay() {
  unsigned long currentMillis = millis();  // Get the current time
   //Perfrom continious task
    
    
  // Check if it's time to perform the task
   if (currentMillis - previousMillis_100MS >= MS_100) {
    // Update the last execution time
    previousMillis_100MS = currentMillis;
    // Perform the task
    getPitotSpeed();
  }
  
  if (currentMillis - previousMillis >= packetTimePeriod) {
    // Update the last execution time
    previousMillis = currentMillis;
    // Perform the task
    periodic_Task();
  }
}
