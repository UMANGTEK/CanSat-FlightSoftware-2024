#include <Servo.h>

//Up Facing --> 22/25/36
//Down Facing --> 23/24/33
 
#define nosePin1 23
#define nosePin2 24
#define nosePin3 33
#define noseDeployAngle 60
#define noseLockAngle 0

#define parachutePin1 22
#define parachutePin2 25
#define parachutePin3 36
#define parachuteDeployAngle 180
#define parachuteLockAngle 0


Servo noseServo1;
Servo noseServo2;
Servo noseServo3;

Servo paraServo1;
Servo paraServo2;
Servo paraServo3;

void servoSetup()
{
    noseServo1.attach(nosePin1);
    noseServo2.attach(nosePin2);
    noseServo3.attach(nosePin3);
    
    paraServo1.attach(parachutePin1);
    paraServo2.attach(parachutePin2);
    paraServo3.attach(parachutePin3);
}

void deployParachute()
{
    // Turn servo to deploy prachute
    paraServo1.write(parachuteDeployAngle);
    paraServo2.write(parachuteDeployAngle);
    paraServo3.write(parachuteDeployAngle);
    return ;
}

void lockPrachute()
{
    // Turn servo to lock prachute
    PARA_DEPLOYED = false;
    paraServo1.write(parachuteLockAngle);
    paraServo2.write(parachuteLockAngle);
    paraServo3.write(parachuteLockAngle);
    return ;
}


void deployNoseCone() 
{
    // Turn servo to release nose cone
    NOSE_RELEASED = true;
    noseServo1.write(noseDeployAngle);
    noseServo2.write(noseDeployAngle);
    noseServo3.write(noseDeployAngle);
    return ;
}

void lockNoseCone()
{
    //Turn servo to lock nose cone
    NOSE_RELEASED = false;
    noseServo1.write(noseLockAngle);
    noseServo2.write(noseLockAngle);
    noseServo3.write(noseLockAngle);
    return ;
}
