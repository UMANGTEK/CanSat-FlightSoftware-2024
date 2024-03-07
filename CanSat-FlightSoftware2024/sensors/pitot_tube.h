#include <Wire.h>
#define SENSOR_ADDRESS 0x28

void setup() 
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() 
{
  Wire.requestFrom(SENSOR_ADDRESS, 2);    // request 2 bytes from sensor
  byte x1 = Wire.read();
  byte x0 = Wire.read();
  
  // Print x1 and x0 in decimal form
  Serial.print("x1 (dec): ");
  Serial.println(x1, DEC);
  Serial.print("x0 (dec): ");
  Serial.println(x0, DEC);
  
  // Concatenate x1 and x0 into one 8-bit decimal value
  uint16_t combinedDec = (x1 * 256) + x0;   // Range of this value (0-16383) If pressure between both outlets is equal, op~ 8192 i.e half of total value
  
  // Print the combined decimal value
  Serial.print("Combined Decimal: ");
  Serial.println(combinedDec);
  
  //-------------extracting temperature signal----------------
//  unsigned temperature = combinedDec;
//  Serial.print("TEMP: ");  Serial.println(temperature, DEC);//
//  Serial.print("TEMP: ");  Serial.println(temperature, BIN);//
//  Serial.println(" ");//
  delay(1000);
}
