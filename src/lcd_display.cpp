#include <LiquidCrystal.h>
#include <Arduino.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Print temperature on the first line
  lcd.setCursor(0, 0);
  lcd.print("coucou");

  // Print humidity on the second line
  // lcd.setCursor(0, 1);
  // lcd.print("Rel. humid.: 81%");
}

void loop() {
  // The loop can be empty for this example
}
