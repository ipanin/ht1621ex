#include "LiquidCrystal7S.h"
#include "MyDisplay.h"

#define SS   2
#define RW   3
#define DATA 4

MyDisplay display(SS, RW, DATA);
LiquidCrystal7S lcd(display, 8, 1);

void setup() {
    lcd.autoscroll();
    lcd.begin();
    lcd.print(123456789);
//    lcd.print("abcdefgh");
//    lcd.print("ijklmno.");
//    lcd.print("rstuvxyz");
}

void loop() {

}