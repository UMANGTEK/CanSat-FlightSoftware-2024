#define battPin 40
#define r1 15
#define r2 33

//voltage*r2/(r1+r2) = vJun

void battSetup()
{
  pinMode(battPin, INPUT_DISABLE);
}

void readVoltage()
{
  float vJun = analogRead(battPin)*3.3/1023; 
  voltage = vJun*(r1 + r2)/r1;
  voltage_percent = ((voltage - 7.6)/(8.0-7.6))*100;
}
