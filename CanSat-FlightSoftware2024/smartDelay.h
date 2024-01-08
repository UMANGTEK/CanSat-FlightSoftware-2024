unsigned long previousMillis = 0;    // Stores the last time the task was executed


void periodic_Task() {
   packet_count++;

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
    //sendDataTelemetry(telemetry_string);
    Serial.println(telemetry_string);
  }

  //Save Data to sd card  
//  saveTelemetryInSdCard(telemetry_string);

  // Save state to EEPROM
  WriteALL();
  
}
//SmartDelay for telemetry packet of 1 second
void smartDelay() {
  unsigned long currentMillis = millis();  // Get the current time
  
  // Check if it's time to perform the task
  if (currentMillis - previousMillis >= packetTimePeriod) {
    // Update the last execution time
    previousMillis = currentMillis;
    
    // Perform the task
    periodic_Task();
  }
}
