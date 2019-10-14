#include "MyDisplay.h"

void MyDisplay::init()
{
    _ht.begin();
    _ht.sendCommand(HT1621::RC256K);
    _ht.sendCommand(HT1621::BIAS_THIRD_3_COM);
    _ht.sendCommand(HT1621::SYS_EN);
    _ht.sendCommand(HT1621::LCD_ON);
}
void MyDisplay::clear()
{
    register uint8_t i;
    for (i = 0; i < HT1621_MAX_ADDR; i++)
        _ht.write(i, 0);
}

void MyDisplay::write(uint8_t pos, uint8_t symbol) {
    uint16_t data = _convert(symbol);
    _ht.write(StartAddress + 3 * pos, data, 12);
}

uint8_t MyDisplay::read(uint8_t pos) {
    return 0;
}

uint16_t MyDisplay::_convert(uint8_t symbol)
{
    return Font[symbol-'0'];
}

/* 0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, , */
const uint16_t MyDisplay::Font[11] = {
    0b001101010011, // 0
    0b000000000011, // 1
    0b001001110001,
    0b000001110011,
    0b000100100011,
    0b000101110010,
    0b001101110010,
    0b000000010011,
    0b001101110011,
    0b000101110011, // 9
    0b00            // space
};
