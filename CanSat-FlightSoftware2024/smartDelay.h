const unsigned long interval = 1000;  // Interval in milliseconds (1 second)
unsigned long previousMillis = 0;    // Stores the last time the task was executed

void smartDelay() {
  unsigned long currentMillis = millis();  // Get the current time
  
  // Check if it's time to perform the task
  if (currentMillis - previousMillis >= interval) {
    // Update the last execution time
    previousMillis = currentMillis;
    
    // Perform the task
    performTask();
  }
}

void performTask() {
  // Your task code here
  
}
