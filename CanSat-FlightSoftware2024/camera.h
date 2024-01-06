#define cameraPin 7

void cameraSetup(){
    pinMode(cameraPin,OUTPUT);
}

void cameraStart( ){
    digitalWrite(cameraPin,LOW);
    smartDelay(200);
    digitalWrite(cameraPin,HIGH);
}

void cameraStop( ){
    digitalWrite(cameraPin,LOW);
    smartDelay(1000);
    digitalWrite(cameraPin,HIGH);
}
