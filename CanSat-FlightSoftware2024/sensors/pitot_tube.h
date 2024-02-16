#include "ms4525do.h"
bfs::Ms4525do pres;

#define STANDARD_PRESSURE 101325.0f  // Standard atmospheric pressure at sea level in Pascals

void pitotSetup() {
  Wire.begin();
  Wire.setClock(400000);
  pres.Config(&Wire, 0x28, 1.0f, -1.0f);
  if (!pres.Begin()) {
    Serial.println("Error communicating with sensor");
    while (1) {}
  }
}


void pitotRead() {
  if (pres.Read()) {
    pitotValid = true;
    float pressGradient = pres.pres_pa();  
    
    float staticPressure = STANDARD_PRESSURE;  
    float airDensity = staticPressure / (287.05 * (pres.die_temp_c() + 273.15));  // R = 287.05 J/(kg·K)

    pitotVelocity = sqrt(2 * pressGradient / airDensity);

    if(pitotVelocity == nan)
      pitotValid = false;
  }
  else {
    pitotValid = false;
  }
}
