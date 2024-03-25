void getAirSpeed(){
  if(bmpValid && pitotValid){
    if((pitotSpeedConstant*(abs(filterPitotVelocity - bmpSpeed))) < 5 ){
      finalAirSpeed = pitotSpeedConstant*filterPitotVelocity + (1-pitotSpeedConstant)*bmpSpeed;  
    }
    else{
      finalAirSpeed = bmpSpeed;
    }     
    speedValid = true;
  }
  else if(bmpValid && !pitotValid){
    finalAirSpeed = bmpSpeed;
    speedValid = true;
  }
  else if(!bmpValid && pitotValid){
    finalAirSpeed = filterPitotVelocity;
    speedValid = true;
  }
  else{
    speedValid = false;
  }
}
