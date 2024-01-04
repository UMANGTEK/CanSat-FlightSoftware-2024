#include <Servo.h>


#define nosePin 29
#define noseDeployAngle 0
#define noseLockAngle 100

#define parachutePin 9
#define parachuteDeployAngle 0
#define parachuteLockAngle 170


Servo noseServo;
Servo paraServo;

void servoSetup()
{
    noseServo.attach(nosePin);
    paraServo.attach(parachutePin);
}

void deployParachute()//////////////////////////////////////////////////////////////////////////////////////////////////
{
    // Turn servo to deploy prachute
    PC_deployed = true ;
    paraServo.write(parachuteDeployAngle);
    return ;
}

void lockPrachute()///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    // Turn servo to lock prachute
    paraServo.write(parachuteLockAngle);
    return ;
}


void deployNoseCone() //////////////////////////////////////////////////////////////////////////////////////////////////
{
    // Turn servo to release nose cone
    noseServo.write(noseDeployAngle);
    return ;
}

void lockNoseCone()
{
    //Turn servo to lock nose cone
    noseServo.write(noseLockAngle);
    return ;
}
