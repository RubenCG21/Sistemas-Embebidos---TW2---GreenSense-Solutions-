#ifndef JOYSTICK_H
#define JOYSTICK_H

#define JOYSTICK_X A1
#define JOYSTICK_Y A0

void initializeJoystick() {
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

int readJoystickX() {
  return analogRead(JOYSTICK_X);
}

int readJoystickY() {
  return analogRead(JOYSTICK_Y);
}

#endif
