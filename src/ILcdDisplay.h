#ifndef _LCD_DYSPLAY_H_INCLUDED_
#define _LCD_DYSPLAY_H_INCLUDED_

#include <inttypes.h>
//#include <string.h>

class ILcdDisplay {
public:
    virtual void init() = 0;

    /// Turn off the display.
    virtual void noDisplay() = 0;

    /// Turn on the display.
    virtual void display() = 0;

    virtual void clear() = 0;

    //virtual size_t write(uint8_t);

    virtual void write(uint8_t pos, uint8_t symbol) = 0;

    virtual uint8_t read(uint8_t pos) = 0;
};

#endif // _LCD_DYSPLAY_H_INCLUDED_