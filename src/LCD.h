#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alterar para 0x3F se necessário

void initializeLCD() {
  lcd.begin(16, 2);
  lcd.backlight();
}

void printTemperature(float temperature) {
  lcd.setCursor(0, 0);
  lcd.print("Temperatura  => ");
   lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" C ");

}

void clearLCD() {
  lcd.clear();
}

void printStartMessage() {
  lcd.setCursor(0, 0);
  lcd.print("Press the button");
}

#endif
