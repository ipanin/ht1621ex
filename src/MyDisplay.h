
void initLCD();

#include "ILcdDisplay.h"

class MyDisplay : public ILcdDisplay {
public:
    /// 3-Wire protocol will be used for the communication.
    MyDisplay(uint8_t ss, uint8_t rw, uint8_t data) : _ht(ss, rw, data) {}

    /// Initialize the LCD with 256KHz internal RC oscillator, 1/3 Bias and 4 COM.
    virtual void init();

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

    static const uint16_t Font[11];
    HT1621 _ht;
    const uint8_t HT1621_MAX_ADDR = 32;
    const uint8_t MaxDigits = 8; ///< Available number of digits in LCD (depend of LCD model)
    const uint8_t StartAddress = 8;
};