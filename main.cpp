
/**
 * +----------------------------------------+
 * | Main Code                              |
 * +----------------------------------------+
 * | @author aeroy-official                 |
 * | @author lehrmanaidins                  |
 * | @version 1.0.0                         |
 * | @date 12/5/2023                        |
 * +----------------------------------------+
 * | JSON Parser:                           |
 * |   https://github.com/nlohmann/json     |
 * | Vector3:                               |
 * |   https://github.com/jimmyberg/Vector3 |
 * +----------------------------------------+
*/

#include <Wire.h> 
#include <MPU6050_tockn.h> 
#include <Servo.h>

#include "telemetry.cpp"
#include "controller.cpp"

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pos = 0;

MPU6050 mpu6050(Wire);

unsigned long timeMilliseconds = 1000UL;

void setup() {
  Controller.initializeControler(mpu6050, "pins.json");
  

  digitalWrite(ledpinr, HIGH);
  digitalWrite(ledping, HIGH);
  digitalWrite(buzzer, HIGH);
}

void loop() {
  mpu6050.update();

  if (timeMilliseconds - millis() <= 0UL) {
    float angleX = mpu6050.getAngleX();
    float angleY = mpu6050.getAngleY();

    printAngles(angleX, angleY);
  }

  if (mpu6050.getAngleX() > -1 && mpu6050.getAngleX() < 1) {
    servo2.write(90);
  } else {
    servo2.write(90 - mpu6050.getAngleY());
  }

  if (mpu6050.getAngleX() == 0) {
    servo1.write(90);
  } else {
    servo1.write(90 + mpu6050.getAngleY());
  }

  // Y-axis / pitch
  if (mpu6050.getAngleY() == 0) {
    servo3.write(90);
  } else {
    servo3.write(90 + mpu6050.getAngleX());
  }

  if (mpu6050.getAngleY() == 0) {
    servo4.write(90);
  } else {
    servo4.write(90 - mpu6050.getAngleX());
  }
}
