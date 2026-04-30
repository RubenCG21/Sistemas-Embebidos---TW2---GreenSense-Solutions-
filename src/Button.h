#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_PIN 8

void initializeButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isButtonPressed() {
  return digitalRead(BUTTON_PIN) == LOW;
}

#endif
