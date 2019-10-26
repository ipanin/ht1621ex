#ifndef _LCD_DISPLAY_H_INCLUDED_
#define _LCD_DISPLAY_H_INCLUDED_

#include <inttypes.h>

class ILcdDisplay {
public:
    virtual void begin() = 0;

    /// Turn off the display.
    virtual void noDisplay() = 0;

    /// Turn on the display.
    virtual void display() = 0;

    virtual void clear() = 0;

    virtual void write(uint8_t pos, uint8_t symbol) = 0;

    virtual uint8_t read(uint8_t pos) = 0;
};

#endif // _LCD_DISPLAY_H_INCLUDED_