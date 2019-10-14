
/**
 * \mainpage Liquid Crystal 7S
 *
 * \author Enrico Formenti
 * \date 14 february 2015
 * \version 1.11
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
 * \section examples The examples
 * Here is a very basic example that initializes the LCD and displays the character 0xBE (on my LCD this is the digit '0') 
 * on all the available places.
 * \snippet LiquidCrystal7S-test.ino Setting all digits to 0xBE
 *
 * And here is a sketch which prints a string of three 0xBE characters ('0' on my LCD).
 * \snippet PrintString.ino Printing a string
 *
 * \section install Installing the library
 * Go into the directory of Arduino's local library (look into the IDE preferences if you don't know where it is). Create a
 * directory named 'LiquidCrystal7S' and copy all the files and the directories that you have found in the zip file.
 *
 * \section todo Todo
 * - Improve the documentation
 * - Improve the printing capabilities
 * - Generalize the library to work also with similar chipsets e.g. HT1623, HT1625, etc.
 *
 * \section histo Version history
 * \subsection v1_0 Version 1.0
 * This is the initial version.
 * \subsection v1_1 Version 1.1
 * - Fixed return value in function LiquidCrystal7S::write(const uint8_t str[])
 * - Variables LiquidCrystal::_curs_col and LiquidCrystal::_curs_row changed from private to protected
 * \subsection v1_11 Version 1.11
 * - Introduced the functions LiquidCrystal7S::autoscroll() and LiquidCrystal7S::noAutoscroll()
 * and the relative control variable LiquidCrystal::_autoscroll
 */

/**
 * \file LiquidCrystal7S.h
 * \brief An adaptation of LiquidCrystal library to deal with 7 segments LCD based on HT1621 chipset.
 * \author Enrico Formenti
 * \date 8 february 2015
 * \version 1.11
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 */

#ifndef LiquidCrystal7S_h
#define LiquidCrystal7S_h

#include <inttypes.h>
#include <string.h>
#include "Print.h"
#include <HT1621.h>

#define HT1621_MAX_ADDR 32
#define TEXT_DIR_LEFT2RIGHT 1
#define TEXT_DIR_RIGHT2LEFT 0

class LiquidCrystal7S : public Print {
public:
    /**
     * \brief Constructor. 3-Wire protocol will be used for the communication.
     */
    LiquidCrystal7S(uint8_t ss, uint8_t rw, uint8_t data);
    /**
     * \brief Constructor. 4-Wire protocol will be used for the communication.
     */
    LiquidCrystal7S(uint8_t ss, uint8_t r, uint8_t w, uint8_t data);
    
    inline ~LiquidCrystal7S() { delete ht; }
    
    /**
     * \brief Init display and configure memory for \c rows and \c cols.
     * @param cols Number of display columns
     * @param rows Number of display rows
     */
    void begin(uint8_t cols, uint8_t rows);
    /**
     * \brief Clear the display
     * \warning Only row and columns are cleared. If the display has 'special' addresses for displaying special symbols
     * then these are not cleared.
     */
    void clear();
    /**
     * \brief Reset cursor position ie. position it at (0,0).
     */
    inline void home() { _curs_col = 0; _curs_row = 0; };
    /**
     * \brief Turn off the display.
     */
    inline void noDisplay() { ht->sendCommand(HT1621::LCD_OFF); };
    /**
     * \brief Turn on the display.
     */
    inline void display()  { ht->sendCommand(HT1621::LCD_ON); };
    /**
     * \brief Scroll all digits 1 position to the left. Lines wrap.
     */
    void scrollDisplayLeft();
    /**
     * \brief Scroll all digits 1 position to the right. Lines wrap.
     */
    void scrollDisplayRight();
    /**
     * \brief Set the writing direction to 'left to right'
     */
    inline void leftToRight() { _text_dir = TEXT_DIR_LEFT2RIGHT; };
    /**
     * \brief Set the writing direction to 'right to left'
     */
    inline void rightToLeft() { _text_dir = TEXT_DIR_RIGHT2LEFT; };
    /**
     * \brief Sets the autoscroll function on.
     */
    inline void autoscroll() { _autoscroll = true; };
    /**
     * \brief Sets the autoscroll function off.
     */
    inline void noAutoscroll() { _autoscroll = false; };
    /**
     * \brief Sets the cursor position
     * @param col Column of the cursor.
     * @param row Row of the cursor.
     * \warning No check is made to verify if the new position is valid.
     */
    //inline void setCursor(uint8_t col, uint8_t row) { _curs_col = col; _curs_row = row; };
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
    
    using Print::write;
protected:
    HT1621  *ht;    
    /**
     * @{
     * @name Cursor position
     */
    uint8_t _curs_col;
    uint8_t _curs_row;
    /** @} */
private:
    /**
     * \brief Initialize the LCD with 256KHz internal RC oscillator, 1/3 Bias and 4 COM.
     */
    void initLCD();
    /**
     * \brief Direction of text writing.
     */
    uint8_t _text_dir;
    /**
     * \brief Keep track is autoscroll function is active or not.
     */
    bool _autoscroll;
    /**
     * @{
     * @name Pins
     * \brief Pins for the serial communication with the HT1621
     */
    /** \brief Read pin. */
    uint8_t _r_pin;
    /** \brief Write pin. */
    uint8_t _w_pin;
    /** \brief Slave select pin */
    uint8_t _ss_pin;
    /** \brief Data pin */
    uint8_t _data_pin;
    /** @} */
    
    /**
     * @{
     * @name Display dimensions
     */
    uint8_t _numrows; /** \brief Number of rows */ 
    uint8_t _numcols; /** \brief Number of columns */
    /** @} */
};

#endif
