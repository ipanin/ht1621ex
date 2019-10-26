#include "LiquidCrystal7S.h"
#include "MyDisplay.h"

#define SS   2
#define RW   3
#define DATA 4

MyDisplay display(SS, RW, DATA);
LiquidCrystal7S lcd(display);

void setup() {
    lcd.begin(8, 1);
//    lcd.print(12345678);
//    lcd.print("abcdefgh");
//    lcd.print("ijklmno.");
    lcd.print("rstuvxyz");
}

void loop() {

}