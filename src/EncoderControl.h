#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#include <Arduino.h>

#define ENCODER_DT A2 // Define pino DT do encoder
#define ENCODER_CLK 7 // Define pino CLK do encoder

extern volatile int encoderPos; // Declaração de variáveis externas
extern volatile int lastPos;

void handleEncoder();
void initializeEncoder();

#endif // ENCODER_CONTROL_H
