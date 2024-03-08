#include <Wire.h>
#define SENSOR_ADDRESS 0x28

void pitotSetup() 
{
  Wire.begin(SENSOR_ADDRESS);        // join i2c bus (address optional for master)
}

void pitotCalibration()
{
   Wire.requestFrom(SENSOR_ADDRESS, 2);    // request 2 bytes from sensor
  byte x1 = Wire.read();
  byte x0 = Wire.read();
  
  // ----------------------------Print x1 and x0 in decimal form
  // Serial.print("x1 (dec): ");
  // Serial.println(x1, DEC);
  // Serial.print("x0 (dec): ");
  // Serial.println(x0, DEC);
  
  // Concatenate x1 and x0 into one 8-bit decimal value
  uint16_t combinedDec = (x1 * 256) + x0;   // Range of this value (0-16383) If pressure between both outlets is equal, op~ 8192 i.e half of total value
  pitotCalibRestValue = combinedDec;  
}

void getPitotSpeed() 
{
  Wire.requestFrom(SENSOR_ADDRESS, 2);    // request 2 bytes from sensor
  byte x1 = Wire.read();
  byte x0 = Wire.read();
  
  // ----------------------------Print x1 and x0 in decimal form
  // Serial.print("x1 (dec): ");
  // Serial.println(x1, DEC);
  // Serial.print("x0 (dec): ");
  // Serial.println(x0, DEC);
  
  // Concatenate x1 and x0 into one 8-bit decimal value
  uint16_t combinedDec = (x1 * 256) + x0;   // Range of this value (0-16383) If pressure between both outlets is equal, op~ 8192 i.e half of total value
   /* 
    *  100 m/s max range ---> 16383 (6465 Pa diff)
    *  0 m/s -----> 8192 (~0 Pa diff)       (107790 - 0)
    *  Considering linear system::::Pdiff =  ---------------- x (combinedDec - 8192)  
    *                                      (16383 - 8192)
   **/
  // -------------Print the combined decimal value----------------------------
  // Serial.print("Combined Decimal: ");
  // Serial.println(combinedDec);
if(combinedDec>16383)
{
  pitotValid = false;
  return;
}
else
{
  pitotValid = true;
}

float pressureDiff = ((6465.0)/(16383.0-8192.0))*(combinedDec - pitotCalibRestValue);
//Serial.print("Ambient Pressure: ");
//Serial.println(pressureDiff);
//Serial.print("Speed: ");
float airDensity = 1.293;
pitotVelocity = sqrt((2*pressureDiff)/airDensity);
//Serial.println(speed); 
  //-------------extracting temperature signal----------------
//  unsigned temperature = combinedDec;
//  Serial.print("TEMP: ");  Serial.println(temperature, DEC);//
//  Serial.print("TEMP: ");  Serial.println(temperature, BIN);//
//  Serial.println(" ");
}
