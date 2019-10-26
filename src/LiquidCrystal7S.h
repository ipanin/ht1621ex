/**
 * \mainpage Liquid Crystal 7S
 *
 * \author Enrico Formenti
 * \tableofcontents
 *
 * \section intro Introduction
 * This project aims at implementing the same functionalities as the classical LiquidCrystal library for 7 segments LCD based on
 * the HT1621 chipset. The LCD is supposed to communicate with the HT1621 through a 3-wire or a 4-wire serial protocol. Remark that
 * this wants to be a generic driver, hence only the basic features of 7 segments display is implemented. All other features such
 * as display of special characters or fine tuning should be implemented in a child class. Indeed, the driver is not aware of
 * how memory is mapped to the LCD.
 *
 * \section config Configuration
 * \subsection init Initialization
 * The display is initialized with 256KHz internal RC clock frequency, 1/3 Bias and 4 Commons. Refer to the manual of class HT1621
 * on how to change these settings.
 * \subsection comm Communication protocol
 * The communication protocol (3-Wire vs. 4-Wire) is chosen at the constructor level. Using the k-parameters constructor selects
 * the k-Wire protocol.
 *
 * \section install Installing the library
 * Go into the directory of Arduino's local library (look into the IDE preferences if you don't know where it is). Create a
 * directory named 'LiquidCrystal7S' and copy all the files and the directories that you have found in the zip file.
 *
 */

/**
 * \file LiquidCrystal7S.h
 * \brief An adaptation of LiquidCrystal library to deal with 7 segments LCD based on HT1621 chipset.
 * \author Enrico Formenti
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 */

#ifndef LiquidCrystal7S_h
#define LiquidCrystal7S_h

#include <Print.h>
#include "ILcdDisplay.h"

class LiquidCrystal7S : public Print {
public:

    /// @param cols Number of display columns
    explicit LiquidCrystal7S(ILcdDisplay& display, uint8_t cols);

    /// Init display
    void begin();

    /**
     * \brief Clear the display
     * \warning Only row and columns are cleared. If the display has 'special' addresses for displaying special symbols
     * then these are not cleared.
     */
    void clear();

    /**
     * \brief Reset cursor position ie. position it at (0,0).
     */
    inline void home() {
        _cursorCol = 0;
    };

    /**
     * \brief Turn off the display.
     */
    inline void noDisplay() { _display.noDisplay(); };

    /**
     * \brief Turn on the display.
     */
    inline void display() { _display.display(); };

    /**
     * \brief Scroll all digits 1 position to the left. Lines wrap.
     */
    void scrollDisplayLeft();

    /**
     * \brief Scroll all digits 1 position to the right. Lines wrap.
     */
    void scrollDisplayRight();

    /**
     * \brief Sets the autoscroll function on.
     */
    inline void autoscroll(bool enabled = true) { _autoscroll = enabled; };

    /**
     * \brief Sets the cursor position
     * @param col Column of the cursor.
     * \warning No check is made to verify if the new position is valid.
     */
    inline void setCursor(uint8_t col) { _cursorCol = col; };
    /**
     * \brief Writes one byte to the LCD memory. This function is used by the 'Print' interface to print 
     * all sort of input types.
     * \warning Child classes should specialize more this function in order to correctly map LCD memory to 
     * LCD printable characters.
     * @param car Character to print
     */
    virtual size_t write(uint8_t);

    /**
     * \brief Writes a string of bytes to the LCD memory. This function is used by the 'Print' interface.
     * \warning Child classes should specialize more this function in order to correctly map LCD memory to 
     * LCD printable characters.
     * @param str String to print.
     * \warning It is assumed that the string is terminated by a '\0' symbol.
     */
    virtual size_t write(const uint8_t str[]);

protected:
    ILcdDisplay& _display;
    uint8_t _cursorCol; ///< Cursor position

private:
    bool _autoscroll; ///< Keep track is autoscroll function is active or not.
    uint8_t _numCols; ///< Number of columns
};

#endif
