#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 3

void initializeBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void buzz() {
  digitalWrite(BUZZER_PIN, HIGH);
}

void silence() {
  digitalWrite(BUZZER_PIN, LOW);
}

#endif
