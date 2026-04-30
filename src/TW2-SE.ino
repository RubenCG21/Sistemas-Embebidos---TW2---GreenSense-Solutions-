#include <Arduino.h>
#include "TemperatureSensor.h"
#include "LCD.h"
#include "Buzzer.h"
#include "Button.h"
#include "WaterLevelSensor.h"
#include "Joystick.h"
#include "ServoMotor.h"
#include "SoilMoistureSensor.h"
#include "StepperMotor.h"
#include "EncoderControl.h" // Include the encoder header file
#include <PCF8574.h> // Include the PCF8574 library

#define MAX_TEMPERATURE 100
#define MIN_TEMPERATURE 25
#define MAX_STEPS 360
#define MIN_STEPS 0
#define SOIL_MOISTURE_THRESHOLD_LOW 30 // Threshold for low soil moisture
#define SOIL_MOISTURE_THRESHOLD_HIGH 70 // Threshold for high soil moisture
PCF8574 pcf8574(0x20); // Define o objeto PCF8574 com o endereço I2C (0x20 é um endereço comum)

const int ledPin = 13; // Define o pino do LED

bool systemStarted = false;
bool menuSelected = false;
int menuOption = 1;
int currentSteps = 0;
int displayOption = 0; // 0: Temperature, 1: Humidity, 2: Water Level

void setup() {
  pinMode(ledPin, OUTPUT); // Define o pino do LED como saída
  initializeTemperatureSensor();
  initializeLCD();
  initializeBuzzer();
  initializeButton();
  initializeWaterLevelSensor();
  initializeJoystick();
  initializeServoMotor();
  initializeStepperMotor();
  initializeEncoder(); // Initialize the encoder
  pcf8574.begin(); // Inicialize o PCF8574
  pcf8574.write8(0xFF);
  
  printStartMessage();
}

void loop() {
  // Check button state
  if (isButtonPressed()) {
    if (!menuSelected) {
      systemStarted = !systemStarted;
      clearLCD();
      if (systemStarted) {
        displayOption = 0;
        printTemperature(readTemperature());
        pcf8574.write8(0xFF); // Ligue todos os LEDs quando o sistema iniciar
      } else {
        printStartMessage();
        silence();
        setServoAngle(0);
        rotateStepperMotorTo(MIN_STEPS);
        currentSteps = MIN_STEPS;
        pcf8574.write8(0x00); // Desligue todos os LEDs quando o sistema parar
      }
      while (isButtonPressed()) {
        // Wait for the button to be released
      }
    } else {
      menuSelected = false;
      clearLCD();
    }
  }

  // Check if the system is on
  if (systemStarted) {
    float temperature = readTemperature();
    printDisplayOption(displayOption, temperature);

    if (temperature > 30) {
      buzz();
    } else {
      silence();
    }

    // Check if the menu is selected
    if (menuSelected) {
      int joyX = readJoystickX();
      if (joyX < 500) {
        clearLCD();
        lcd.setCursor(0, 0);
        lcd.print("Humidity: ");
        lcd.print(encoderPos); // Display humidity on LCD
        lcd.print("%");
        lcd.setCursor(0, 1);
        lcd.print("Water Level: ");
        lcd.print(readWaterLevel()); // Display water level on LCD
      } else if (joyX > 700) {
        menuOption++;
        if (menuOption > 1) {
          menuOption = 1;
        }
        clearLCD();
        lcd.setCursor(0, 0);
        lcd.print("Menu:");
        lcd.setCursor(0, 1);
        lcd.print("1. View Humidity");
      }
    } else {
      switch (menuOption) {
        case 1:
          int joyX = readJoystickX();
          if (joyX < 500) {
            clearLCD();
            lcd.setCursor(0, 0);
            lcd.print("Humidity: ");
            lcd.print(encoderPos);
            lcd.print("%");
          }
          break;
      }
    }

    // Check soil moisture and actuate servo motor accordingly
    int soilMoisture = encoderPos; // Atualiza a umidade do solo com base na posição do encoder
    if (soilMoisture < SOIL_MOISTURE_THRESHOLD_LOW) {
      setServoAngle(180); // Correct angle for the servo motor
    } else if (soilMoisture > SOIL_MOISTURE_THRESHOLD_HIGH) {
      setServoAngle(-180); // Correct angle for the servo motor
    }

    // Adjust stepper motor based on temperature
    int targetSteps = map(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE, MIN_STEPS, MAX_STEPS);
    if (targetSteps > currentSteps) {
      rotateStepperMotor(targetSteps - currentSteps);
      currentSteps = targetSteps;
    } else if (targetSteps < currentSteps) {
      rotateStepperMotor(currentSteps - targetSteps);
      currentSteps = targetSteps;
    }
  } else {
    if (!isButtonPressed() && !menuSelected) {
      int joyY = readJoystickY();
      if (joyY < 500) {
        menuSelected = true;
        clearLCD();
        lcd.setCursor(0, 0);
        lcd.print("Menu");
        lcd.setCursor(0, 1);
        lcd.print("1. View Humidity");
      }
    }
  }

  // Check joystick for changing display information
  int joyX = readJoystickX();
  if (joyX > 700) { // Right movement
    displayOption = (displayOption + 1) % 3;
    delay(300); // Debounce delay
  }
}

void printDisplayOption(int option, float temperature) {
  clearLCD();
  switch (option) {
    case 0:
      printTemperature(temperature);
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.print(encoderPos);
      lcd.print("%");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Water Level: ");
      lcd.print(readWaterLevel());
      break;
  }
}

void rotateStepperMotorTo(int targetSteps) {
  int stepsToMove = targetSteps - currentSteps;
  rotateStepperMotor(stepsToMove);
}
