#include "EncoderControl.h"

volatile int encoderPos = 50; // Posição inicial do encoder (simulada)
volatile int lastPos = -1;

void handleEncoder() {
  int DT = digitalRead(ENCODER_DT);
  int CLK = digitalRead(ENCODER_CLK);
  if (DT != lastPos) {
    if (CLK != DT) {
      encoderPos++;
    } else {
      encoderPos--;
    }
    if (encoderPos > 100) encoderPos = 100; // Limita o valor máximo
    if (encoderPos < 0) encoderPos = 0;     // Limita o valor mínimo
    lastPos = DT;
  }
}

void initializeEncoder() {
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_CLK, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT), handleEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), handleEncoder, CHANGE);
}
