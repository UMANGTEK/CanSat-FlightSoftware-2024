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
        EEwriteFloat(zero_alt_calib, 4);
        EEwriteInt(NOSE_RELEASED, 5);
        EEwriteInt(PARA_DEPLOYED, 6);
        EEwriteInt(BCN, 7);
        EEwriteInt(simFlag, 8);
}
