/**
 * \file LiquidCrystal7S.cpp
 * \brief Implementation of an adaptation of LiquidCrystal library to deal with 7 segments LCD based on HT1621 chipset.
 * \author Enrico Formenti
 * \date 8 february 2015
 * \version 1.1
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 */

#include "LiquidCrystal7S.h"

LiquidCrystal7S::LiquidCrystal7S(ILcdDisplay& display, uint8_t cols, uint8_t lines)
: _display(display), _numCols(cols), _numRows(lines), _text_dir(TEXT_DIR_LEFT2RIGHT), _autoscroll(false){
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

    // rotate each row independent
    for (uint8_t i = 0; i < _numRows; i++) {
        uint8_t firstInCurrentRow = i * _numCols;
        uint8_t lastInCurrentRow = (i+1) * _numCols - 1;
        uint8_t savedFirst = _display.read(firstInCurrentRow);

        for (uint8_t j = firstInCurrentRow; j < lastInCurrentRow; j++) {
            _display.write(j, _display.read(j + 1));
        }

        _display.write(lastInCurrentRow, savedFirst);
    }
}

void LiquidCrystal7S::scrollDisplayRight() {
    _cursorCol = (_cursorCol + 1) % _numCols; // move cursor right circular

    // rotate each row independent
    for (uint8_t i = 0; i < _numRows; i++) {
        uint8_t firstInCurrentRow = i * _numCols;
        uint8_t lastInCurrentRow = (i+1) * _numCols - 1;
        uint8_t saveLast = _display.read(lastInCurrentRow);

        for (uint8_t j = lastInCurrentRow; j > firstInCurrentRow; j--) {
            _display.write(j, _display.read(j - 1));
        }
        _display.write(firstInCurrentRow, saveLast);
    }
}

size_t LiquidCrystal7S::write(uint8_t value) {
    if (_autoscroll) {
        if (_text_dir == TEXT_DIR_LEFT2RIGHT && (_cursorCol + 1 >= _numCols)) {
            scrollDisplayLeft();
        }
        else if (_text_dir == TEXT_DIR_RIGHT2LEFT && (_cursorCol == 0)) {
            scrollDisplayRight();
        }
    }

    _display.write(_cursorRow * _numCols + _cursorCol, value);

    // update cursor position according to direction
    if (_text_dir == TEXT_DIR_LEFT2RIGHT) {
        _cursorCol = (_cursorCol + 1) % _numCols;
    }
    else { // _text_dir = TEXT_DIR_RIGHT2LEFT
        _cursorCol = (_cursorCol + _numCols - 1) % _numCols;
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