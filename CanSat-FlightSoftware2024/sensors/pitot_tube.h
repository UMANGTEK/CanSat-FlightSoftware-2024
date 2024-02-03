#include "ms4525do.h"
bfs::Ms4525do pres;

#define STANDARD_PRESSURE 101325.0f  // Standard atmospheric pressure at sea level in Pascals

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Wire.begin();
  Wire.setClock(400000);
  pres.Config(&Wire, 0x28, 1.0f, -1.0f);
  if (!pres.Begin()) {
    Serial.println("Error communicating with sensor");
    while (1) {}
  }
}

void loop() {
  if (pres.Read()) {

    float pressGradient = pres.pres_pa();  
    //Serial.println(pressGradient);
    
    float staticPressure = STANDARD_PRESSURE;  
    float airDensity = staticPressure / (287.05 * (pres.die_temp_c() + 273.15));  // R = 287.05 J/(kg·K)

    float airspeed = sqrt(2 * pressGradient / airDensity);
    Serial.print("Airspeed: ");
    Serial.print(airspeed , 6);  
    Serial.println(" m/s");
  }
  delay(10);
}