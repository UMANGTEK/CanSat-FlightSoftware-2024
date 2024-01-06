const unsigned long interval = 1000;  // Interval in milliseconds (1 second)
unsigned long previousMillis = 0;    // Stores the last time the task was executed

void smartDelay() {
  unsigned long currentMillis = millis();  // Get the current time
  
  // Check if it's time to perform the task
  if (currentMillis - previousMillis >= interval) {
    // Update the last execution time
    previousMillis = currentMillis;
    
    // Perform the task
    repetitive_Task();
  }
}

void repetitive_Task() {
   packet_count ++;

  // Read Sensor Data
  //GPS data
  gpsGetTime( &gpsSecond , &gpsMinute, &gpsHour , &gpsDay, &gpsMonth , &gpsYear , &dateValid , &timeValid);
  gpsReading(&noSats , &lat , &lng , &gpsAltitude , &satsValid, &locValid  , &altValid );
  //BNO data
  bnoGetValues();
  readVoltage();
  //BMP data
  bmpGetValues();

  // Apply filter


  //Process recieved commmands
  //get packet
  if ( packetAvailable() ) {
    String packetRecieved = getOnePacket();
    packetCheck(packetRecieved);
  }

  updateAlt(adjusted_alt);
  //Make telemetry packet
  String telemetry_string = makeTelemetryPacket();

  //Transmit data to GCS over Xbee
  if ( telemetry ){
    sendDataTelemetry(telemetry_string);
  }

  //Save Data to sd card  
  saveTelemetryInSdCard(telemetry_string);

  // Save state to EEPROM
  WriteALL();
  
}
