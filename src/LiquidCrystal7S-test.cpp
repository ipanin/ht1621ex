#include "LiquidCrystal7S.h"
#include "MyDisplay.h"

#define SS   2
#define RW   3
#define DATA 4

MyDisplay display(SS, RW, DATA);
LiquidCrystal7S lcd(display, 8);
char c = 32;

void setup() {
    lcd.autoscroll();
    lcd.begin();
//    lcd.print(76302817);
//    lcd.print(-1234.56);
}

void loop() {
    lcd.print(c);
    delay(500);
    if (++c >= 127)
        c = 32;

}