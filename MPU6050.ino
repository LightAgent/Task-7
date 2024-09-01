#include <Wire.h>


// Sources
// https://playground.arduino.cc/Main/MPU-6050/#short
// https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/
// ChatGPT

const int MPU6050_ADDR = 0x68;

const int PWR_MGMT_1 = 0x6B;
const int GYRO_XOUT_H = 0x43;
const int GYRO_YOUT_H = 0x45;
const int GYRO_ZOUT_H = 0x47;
const int ACCEL_XOUT_H = 0x3B;
const int ACCEL_YOUT_H = 0x3D;
const int ACCEL_ZOUT_H = 0x3F;

int16_t gyroZ_raw;
int16_t accelX_raw, accelY_raw, accelZ_raw;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  gyroZ_raw = readMPU6050(GYRO_ZOUT_H);
  
  accelX_raw = readMPU6050(ACCEL_XOUT_H);
  accelY_raw = readMPU6050(ACCEL_YOUT_H);
  accelZ_raw = readMPU6050(ACCEL_ZOUT_H);
  
  float yaw = gyroZ_raw / 131.0; // Convert raw value to degrees per second

  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.println(" deg/s");
  
  delay(100); // Delay for stability in readings
}

int16_t readMPU6050(uint8_t regAddr) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(regAddr);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 2, true);
  
  int16_t rawData = Wire.read() << 8 | Wire.read();
  return rawData;
}
