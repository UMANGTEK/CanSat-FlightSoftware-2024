unsigned long previousMillisLEDS = 0;
#define redLED 10
#define blueLED 12
#define greenLED 11
#define buzzerPIN 2

void led_buzzer_Setup(){
    pinMode(redLED,OUTPUT);
    pinMode(blueLED,OUTPUT);
    pinMode(greenLED,OUTPUT);
    pinMode(buzzerPIN,OUTPUT);
}

void blink(int pin, long duration) {
  unsigned long currentMillisLED = millis(); // Get the current time
  
  // Check if it's time to blink the LED
  if (currentMillisLED - previousMillisLEDS >= duration) {
    previousMillisLEDS = currentMillisLED; // Save the last time the LED was updated

    // Toggle the LED state
    if (digitalRead(pin) == LOW) {
      digitalWrite(pin, HIGH); // Turn the LED on
    } else {
      digitalWrite(pin, LOW); // Turn the LED off
    }
  }
}


void buzzerON(){
    digitalWrite(buzzerPIN,HIGH);
    BCN = true;
}
void buzzerOFF(){
    digitalWrite(buzzerPIN,LOW);
    BCN = false;
}

//LED ON
void redON(){
    digitalWrite(redLED,HIGH);
}
void blueON(){
    digitalWrite(blueLED,HIGH);
}
void greenON(){
    digitalWrite(greenLED,HIGH);
}

// LED OFF
void redOFF(){
    digitalWrite(redLED,LOW);
}
void blueOFF(){
    digitalWrite(blueLED,LOW);
}
void greenOFF(){
    digitalWrite(greenLED,LOW);
}
