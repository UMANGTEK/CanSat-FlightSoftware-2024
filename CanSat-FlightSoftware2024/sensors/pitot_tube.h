#include <Wire.h>
#define SENSOR_ADDRESS 0x28
#include <Arduino.h>

class KalmanFilter {
  public:
    KalmanFilter(float dt, float process_noise, float measurement_noise) {
      this->dt = dt;  // time step
      A[0][0] = 1;
      A[0][1] = dt;
      A[1][0] = 0;
      A[1][1] = 1;
      
      H[0][0] = 1;  // measurement matrix

      this->process_noise = process_noise;  // process noise covariance
      this->measurement_noise = measurement_noise;  // measurement noise covariance

      Q[0][0] = process_noise;
      Q[0][1] = 0;
      Q[1][0] = 0;
      Q[1][1] = process_noise;

      R[0][0] = measurement_noise;

      P[0][0] = 0;
      P[0][1] = 0;
      P[1][0] = 0;
      P[1][1] = 0;

      x[0][0] = 0;  // initial state
      x[1][0] = 0;
    }

    void predict() {
      // Predict the next state
      float temp[2][1];
      multiply(A, x, temp);
      memcpy(x, temp, sizeof(x));

      float temp2[2][2];
      multiply(A, P, temp2);
      transpose(A, temp2);
      multiply(temp2, P, P);
      add(P, Q, P);
    }

    void update(float z) {
      // Update the state based on measurement
      float y = z - H[0][0] * x[0][0];
      float S = H[0][0] * P[0][0] * H[0][0] + R[0][0];
      float K[2][1];
      K[0][0] = P[0][0] * H[0][0] / S;
      K[1][0] = P[1][0] * H[0][0] / S;

      x[0][0] = x[0][0] + K[0][0] * y;
      x[1][0] = x[1][0] + K[1][0] * y;

      P[0][0] = (1 - K[0][0] * H[0][0]) * P[0][0];
      P[1][0] = (1 - K[1][0] * H[0][0]) * P[1][0];
    }

    float getVelocity() {
      return x[0][0];
    }

  private:
    float dt;  // time step
    float A[2][2];  // state transition matrix
    float H[1][2];  // measurement matrix
    float process_noise;  // process noise covariance
    float measurement_noise;  // measurement noise covariance
    float Q[2][2];  // process noise covariance matrix
    float R[1][1];  // measurement noise covariance matrix
    float P[2][2];  // state covariance matrix
    float x[2][1];  // state vector

    void multiply(float a[][2], float b[][1], float result[][1]) {
      result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
      result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    }

    void multiply(float a[][2], float b[][2], float result[][2]) {
      result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
      result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
      result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
      result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    }

    void add(float a[][2], float b[][2], float result[][2]) {
      result[0][0] = a[0][0] + b[0][0];
      result[0][1] = a[0][1] + b[0][1];
      result[1][0] = a[1][0] + b[1][0];
      result[1][1] = a[1][1] + b[1][1];
    }

    void transpose(float matrix[][2], float result[][2]) {
      result[0][0] = matrix[0][0];
      result[0][1] = matrix[1][0];
      result[1][0] = matrix[0][1];
      result[1][1] = matrix[1][1];
    }
};

void pitotSetup() 
{
  Wire.begin(SENSOR_ADDRESS);        // join i2c bus (address optional for master)
}

void pitotCalibration()
{
   Wire.requestFrom(SENSOR_ADDRESS, 2);    // request 2 bytes from sensor
  byte x1 = Wire.read();
  byte x0 = Wire.read();
  
  // ----------------------------Print x1 and x0 in decimal form
  // Serial.print("x1 (dec): ");
  // Serial.println(x1, DEC);
  // Serial.print("x0 (dec): ");
  // Serial.println(x0, DEC);
  
  // Concatenate x1 and x0 into one 8-bit decimal value
  uint16_t combinedDec = (x1 * 256) + x0;   // Range of this value (0-16383) If pressure between both outlets is equal, op~ 8192 i.e half of total value
  pitotCalibRestValue = combinedDec;  
}

void getPitotSpeed() 
{
  KalmanFilter kf(dt, process_noise, measurement_noise);
  Wire.requestFrom(SENSOR_ADDRESS, 2);    // request 2 bytes from sensor
  byte x1 = Wire.read();
  byte x0 = Wire.read();
  
  // ----------------------------Print x1 and x0 in decimal form
  // Serial.print("x1 (dec): ");
  // Serial.println(x1, DEC);
  // Serial.print("x0 (dec): ");
  // Serial.println(x0, DEC);
  
  // Concatenate x1 and x0 into one 8-bit decimal value
  uint16_t combinedDec = (x1 * 256) + x0;   // Range of this value (0-16383) If pressure between both outlets is equal, op~ 8192 i.e half of total value
   /* 
    *  100 m/s max range ---> 16383 (6465 Pa diff)
    *  0 m/s -----> 8192 (~0 Pa diff)       (107790 - 0)
    *  Considering linear system::::Pdiff =  ---------------- x (combinedDec - 8192)  
    *                                      (16383 - 8192)
   **/
  // -------------Print the combined decimal value----------------------------
  // Serial.print("Combined Decimal: ");
  // Serial.println(combinedDec);
if(combinedDec>16383)
{
  pitotValid = false;
  return;
}
else
{
  pitotValid = true;
}

float pressureDiff = ((6465.0)/(16383.0-8192.0))*(combinedDec - pitotCalibRestValue);
float airDensity = 1.293;
float pitotVelocity = sqrt((2*pressureDiff)/airDensity);
kf.predict();
kf.update(pitotVelocity);
filterPitotVelocity = kf.getVelocity();
}
