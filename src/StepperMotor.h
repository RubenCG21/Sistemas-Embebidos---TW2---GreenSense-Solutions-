#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#define STEPS_PER_REVOLUTION 2048 // Número de passos por revolução do motor de passo

#define COIL_A_PIN 2
#define COIL_B_PIN 4
#define COIL_C_PIN 5
#define COIL_D_PIN 6

int stepCounter = 0;

void initializeStepperMotor() {
  pinMode(COIL_A_PIN, OUTPUT);
  pinMode(COIL_B_PIN, OUTPUT);
  pinMode(COIL_C_PIN, OUTPUT);
  pinMode(COIL_D_PIN, OUTPUT);
}

void stepMotor() {
  switch (stepCounter % 4) {
    case 0: // Coil A active
      digitalWrite(COIL_A_PIN, HIGH);
      digitalWrite(COIL_B_PIN, LOW);
      digitalWrite(COIL_C_PIN, LOW);
      digitalWrite(COIL_D_PIN, LOW);
      break;
    case 1: // Coil B active
      digitalWrite(COIL_A_PIN, LOW);
      digitalWrite(COIL_B_PIN, HIGH);
      digitalWrite(COIL_C_PIN, LOW);
      digitalWrite(COIL_D_PIN, LOW);
      break;
    case 2: // Coil C active
      digitalWrite(COIL_A_PIN, LOW);
      digitalWrite(COIL_B_PIN, LOW);
      digitalWrite(COIL_C_PIN, HIGH);
      digitalWrite(COIL_D_PIN, LOW);
      break;
    case 3: // Coil D active
      digitalWrite(COIL_A_PIN, LOW);
      digitalWrite(COIL_B_PIN, LOW);
      digitalWrite(COIL_C_PIN, LOW);
      digitalWrite(COIL_D_PIN, HIGH);
      break;
  }
  stepCounter++;
}

void rotateStepperMotor(int steps) {
  for (int i = 0; i < steps; i++) {
    stepMotor();
    delay(5); // Ajuste o atraso conforme necessário para a velocidade do motor
  }
}

#endif
