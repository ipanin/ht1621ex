#include "LiquidCrystal7S.h"

#define SS   2
#define RW   3
#define DATA 4

LiquidCrystal7S lcd(SS, RW, DATA);

void setup() {
  lcd.begin(8, 1);
  lcd.print(12345678); 
}

void loop() {
	
}