#ifndef WATER_LEVEL_SENSOR_H
#define WATER_LEVEL_SENSOR_H

#define TRIGGER_PIN 11
#define ECHO_PIN 12

void initializeWaterLevelSensor() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readWaterLevel() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Convertendo para centímetros
  
  return distance;
}

#endif
