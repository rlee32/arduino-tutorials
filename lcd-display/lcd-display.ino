// Author: Robert Lee
// Email: rlee32@gatech.edu

// This is derived from a tutorial found on the official arduino website: 
// http://www.arduino.cc/en/Tutorial/LiquidCrystal

const static int LCD_COLUMNS = 20;
const static int LCD_ROWS = 4;
// Pins to recieve LCD outputs
const static int RS_PIN = 7;
const static int ENABLE_PIN = 6;
const static int D4_PIN = 5;
const static int D5_PIN = 4;
const static int D6_PIN = 3;
const static int D7_PIN = 2;
// LCD VSS and RW_PIN pins go to ground.
// LCD VCC goes to Arduino 5V. 

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

void setup()
{
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.print("hello, world!");
}

void loop()
{
  lcd_print(1, (int) (millis() / 1000) );
  lcd_print(3, "Testing out this row");
}

void lcd_print(int row, const char* literal)
{
  lcd.setCursor(0, row);
  lcd.print(literal);
}
void lcd_print(int row, double number)
{
  lcd.setCursor(0, row);
  lcd.print(number);
}
void lcd_print(int row, int number)
{
  lcd.setCursor(0, row);
  lcd.print(number);
}


