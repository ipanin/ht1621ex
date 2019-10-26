#ifndef _MY_DISPLAY_H_INCLUDED_
#define _MY_DISPLAY_H_INCLUDED_

#include "ILcdDisplay.h"
#include "HT1621.h"

class MyDisplay : public ILcdDisplay {
public:
    /// 3-Wire protocol will be used for the communication.
    MyDisplay(uint8_t ss, uint8_t rw, uint8_t data) : _ht(ss, rw, data) {}

    /// Initialize the LCD with 256KHz internal RC oscillator, 1/3 Bias and 4 COM.
    virtual void begin();

    /// clear display
    virtual void clear();

    /// Turn off the display.
    virtual inline void noDisplay() { _ht.sendCommand(HT1621::LCD_OFF); };

    /// Turn on the display.
    virtual inline void display() { _ht.sendCommand(HT1621::LCD_ON); };

    virtual void write(uint8_t pos, uint8_t symbol);

    virtual uint8_t read(uint8_t pos);

private:
    uint16_t _convert(uint8_t symbol);

    static const uint16_t Ascii[128];
    static const uint8_t MaxDigits = 8; ///< Available number of digits in my LCD
    uint8_t _buffer[MaxDigits];
    HT1621 _ht;
};

#endif // _MY_DISPLAY_H_INCLUDED_