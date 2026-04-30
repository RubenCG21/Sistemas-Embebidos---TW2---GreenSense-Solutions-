#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Servo.h>

#define SERVO_PIN 10

Servo servo;

void initializeServoMotor() {
  servo.attach(SERVO_PIN);
}

void setServoAngle(int angle) {
  servo.write(angle);
}

#endif
