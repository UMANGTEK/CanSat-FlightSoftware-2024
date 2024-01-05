#include <EEPROM.h>

float EEreadFloat( int n ){
      unsigned int eeAddress = ( sizeof(float)>sizeof(int) ? sizeof(float) : sizeof(int)) *n;
      float data = 0.00f;  
      EEPROM.get( eeAddress , data );
      return data;
}

int EEreadInt( int n ){
      unsigned int eeAddress = ( sizeof(float)>sizeof(int) ? sizeof(float) : sizeof(int)) *n;
      int data = 0;  
      EEPROM.get( eeAddress , data );
      return data;
}

void EEwriteFloat( float data , int n ){
      unsigned int eeAddress = ( sizeof(float)>sizeof(int) ? sizeof(float) : sizeof(int)) *n;
      EEPROM.put( eeAddress , data );
}

void EEwriteInt( int data , int n ){
      unsigned int eeAddress = ( sizeof(float)>sizeof(int) ? sizeof(float) : sizeof(int)) *n;
      EEPROM.put( eeAddress , data );
}

void WriteALL(){
        EEwriteInt(currentState , 1);
        EEwriteInt(currentMode, 2);
        EEwriteInt(packet_count, 3);
        EEwriteInt(zero_alt_calib, 4);
        EEwriteInt(HS_deployed, 5);
        EEwriteInt(PC_deployed, 6);
        EEwriteInt(MAST_raised, 7);
}
