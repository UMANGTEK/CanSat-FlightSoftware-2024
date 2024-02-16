#define battPin 41
#define r1 340
#define r2 98

//voltage*r2/(r1+r2) = vJun

void battSetup()
{
  pinMode(battPin, INPUT);
}

void readVoltage()
{
  float vJun = analogRead(battPin)*3.3/1023; 
  voltage = vJun*2.6585;
}
