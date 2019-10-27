/**
 * \file LiquidCrystal7S.cpp
 * \brief Implementation of an adaptation of LiquidCrystal library to deal with 7 segments LCD based on HT1621 chipset.
 * \author Enrico Formenti
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 */

#include "LiquidCrystal7S.h"

LiquidCrystal7S::LiquidCrystal7S(ILcdDisplay& display, uint8_t cols)
: _display(display), _numCols(cols), _autoscroll(false), _cursorCol(0){
}

void LiquidCrystal7S::begin() {
    _display.begin();
    clear();
}

void LiquidCrystal7S::clear() {
    _display.clear();
    home();
}

void LiquidCrystal7S::scrollDisplayLeft() {
    _cursorCol = (_cursorCol + _numCols - 1) % _numCols; // move cursor left circular

    // rotate row
    uint8_t lastInCurrentRow = _numCols - 1;
    uint8_t savedFirst = _display.read(0);

    for (uint8_t j = 0; j < lastInCurrentRow; j++) {
        _display.write(j, _display.read(j + 1));
    }

    _display.write(lastInCurrentRow, savedFirst);
}

void LiquidCrystal7S::scrollDisplayRight() {
    _cursorCol = (_cursorCol + 1) % _numCols; // move cursor right circular

    // rotate row
    uint8_t lastInCurrentRow = _numCols - 1;
    uint8_t saveLast = _display.read(lastInCurrentRow);

    for (uint8_t j = lastInCurrentRow; j > 0; j--) {
        _display.write(j, _display.read(j - 1));
    }

    _display.write(0, saveLast);
}

size_t LiquidCrystal7S::write(uint8_t value) {
    if (_autoscroll && _cursorCol >= _numCols) { // scroll if cursor out of bound
        scrollDisplayLeft();
    }

    _display.write(_cursorCol++, value);

    if (!_autoscroll && _cursorCol >= _numCols) {
        _cursorCol = 0;
    }

    // assume success
    return 1;
}

size_t LiquidCrystal7S::write(const uint8_t str[]) {
    size_t i = 0;

    while(str[i]) {
        write(str[i++]);
    }
    // assume success
    return i;
}