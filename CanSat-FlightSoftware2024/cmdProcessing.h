void parsePacket( String packet , String *arr , int n , char a )
{
    unsigned int pos = 0;
    for (int i = 0 ; (pos = packet.indexOf(a)) != packet.length() && i < n-1 ; i++ )
    {
        arr[i] = packet.substring(0, pos);
        packet = packet.substring(pos + 1);
    }   
    arr[n-1] = packet;
    
}

bool ST(String p[])
{   
    if ( p[3] == "GPS" ){
        //set time using gps
        setTimeGps();
        return true;
    }
    else{
        String arr[3];
        int arrInt[3];
        parsePacket(p[3],arr,3,':');

        for ( int i = 0 ; i < 3; i++ ){
            arrInt[i] = arr[i].toInt(); 
            if ( arr[i] != "00" && arrInt[i] == 0 ){
                return false;
            }
        }

        int hr = arrInt[0];
        int min = arrInt[1];
        int sec = arrInt[2];
        //set RTCtime 
        setTime_td(hr,min,sec);
        return true;
    }
}

void packetCheck(String packet)
{
    int no_of_fields = 4 ;
    String p[4] = {"","","",""};
    parsePacket(packet,p,no_of_fields,',');
    if (p[2] == "CX")                          // Compulsory Telemetrry on/off command
    {
        if (p[3] == "ON"){
            telemetry = true;
            CMD_ECHO="CX";
        }
        else if (p[3] == "OFF")
        {
            telemetry = false;
            CMD_ECHO="CX";
        }
    }
    else if (p[2] == "ST")                   // Compulsory set time command
    {
        if ( ST(p) ){
            CMD_ECHO="ST";
        }
    }
    else if (p[2] == "SIM")                                 //Compulsory simulation toggle and control command
    {
        if ( currentState == LAUNCH_WAIT ){
            if (p[3] == "ENABLE"){
                simulation_enabled = true ;
                CMD_ECHO="SIM";
            }
            else if (p[3] == "DISABLE"){
                simulation_enabled = false;
                currentMode = FLIGHT;
                CMD_ECHO="SIM";
            }
            else if (p[3] == "ACTIVATE" && simulation_enabled){
                currentMode = SIMULATION;
                CMD_ECHO="SIM";
                zero_alt_calib = 0 ;
            }
        }
    }
    else if (p[2] == "SIMP")                                      // Compulsory simulared pressure data receiving command
    {
        //Set pressure to recieved value 
        if ( currentMode == SIMULATION ){
            float tempPressure = p[3].toFloat();
            if ( tempPressure != 0 ){
                adjusted_pressure= tempPressure/100;
                // impliment conversion from pressure to altitude 
                // 44330 * [1 - (P/p0)^(1/5.255) ]
                adjusted_alt=( 44330 * ( 1 - pow( (adjusted_pressure/ 1013.25 ), (1/5.225) )  )) - zero_alt_calib;
                updateAlt(adjusted_alt);
                pressureValid = true;
                CMD_ECHO="SIMP";
            }
        }
    }
    else if (p[2] == "CAL")                                             // Compulsory altitude calibration command    
    {
        //Set zero alt calibration ( only if in LAUNCH_WAIT mode )
        if ( currentState == LAUNCH_WAIT ){
            if( currentMode == FLIGHT  ){
                bmpGetValues();
                if (bmpValid){
                    zero_alt_calib = altitude;
                    WriteALL();
                    CMD_ECHO = "CAL";
                }
            }
            else if ( currentMode == SIMULATION ){
                zero_alt_calib = adjusted_alt;
                adjusted_alt = 0;
                WriteALL();
                CMD_ECHO = "CAL";
            }
        }
    }


     else if (p[2] == "BCN")
    {
        CMD_ECHO = "BCN";
        if(p[3] == "ON")
          buzzerON();
        else if (p[3] == "OFF")
          buzzerOFF();
    }
   
    else if (p[2] == "LAUNCH_WAIT")
    {
        currentState = LAUNCH_WAIT;
        WriteALL();
    }
    /*
     * no need because it is taken care by SIM command
     else if (p[2] == "MODE")
     {
    //only if in idle mode
    if (p[3] == "F")
    {
    currentMode = FLIGHT; 
    }
    }
    else if (p[2] == "CAL_TILT")
    {
        if ( currentState == LAUNCH_WAIT ){
            tilt_calibration = true;
            CMD_ECHO = "CAL_TILT";
        }
    }*/
    
    else if ( p[2] == "RESET" ){
        lockNoseCone();
        lockPrachute();
        buzzerOFF();
        currentState = LAUNCH_WAIT ;
        currentMode = FLIGHT ;
        packet_count = 0;
        NOSE_RELEASED = false;
        PARA_DEPLOYED = false;
        telemetry = true;
        tilt_calibration = false ;
        simulation_enabled = false;
        CMD_ECHO = "RESET";
        
         if (bmpValid){
          bmpGetValues();
          zero_alt_calib = altitude;
          WriteALL();
         }
         else{
          CMD_ECHO = "RESET_FAILED";
         }
    }
  
    else if ( p[2] == "DEPLOY_PARA" ){
        deployParachute();
        CMD_ECHO = "DEPLOY_PARA";
        PARA_DEPLOYED = true ;
        WriteALL();
    }
    else if ( p[2] == "LOCK_PARA" ){
        lockPrachute();
        CMD_ECHO = "LOCK_PARA";
        WriteALL();
    }
    else if ( p[2] == "DEPLOY_NOSE" ){
        deployNoseCone();
        CMD_ECHO = "DEPLOY_NOSE";
        WriteALL();
    }
     else if ( p[2] == "LOCK_NOSE" ){
        lockNoseCone();
        CMD_ECHO = "LOCK_NOSE";
        WriteALL();
    }
}
