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

LiquidCrystal7S::LiquidCrystal7S(ILcdDisplay& pDisplay) {
    _ht = pDisplay;
    _ht.init();
}

void LiquidCrystal7S::begin(uint8_t cols, uint8_t lines) {
    _numcols = cols;
    _numrows = lines;
    _text_dir = TEXT_DIR_LEFT2RIGHT;
    _autoscroll = false;

    clear();
}

void LiquidCrystal7S::clear() {
    _ht.clear();
    home();
}

void LiquidCrystal7S::scrollDisplayLeft(void) {
    register uint8_t i, j;
    register uint8_t saveFirst;

    _curs_col = (_curs_col + _numcols - 1) % _numcols; // move cursor right

    for (i = 0; i < _numrows; i++) {
        saveFirst = ht.read(i * _numcols);
        for (j = _numcols - 1; j > 0; j--)
            ht.write(i * _numcols + j, ht.read(i * _numcols + j + 1));
        _ht.write((i + 1) * _numcols - 1, saveFirst);
    }
}

void LiquidCrystal7S::scrollDisplayRight(void) {
    register uint8_t i, j;
    register uint8_t saveLast;

    _curs_col = (_curs_col + 1) % _numcols; // move cursor right

    for (i = 0; i < _numrows; i++) {
        saveLast = _ht.read((i + 1) * _numcols - 1);
        for (j = 1; j < _numcols; j++)
            _ht.write(i * _numcols + j, _ht.read(i * _numcols + j - 1));
        _ht.write(i * _numcols, saveLast);
    }
}

size_t LiquidCrystal7S::write(uint8_t value) {
    if (_autoscroll) {
        if (_text_dir == TEXT_DIR_LEFT2RIGHT && (_curs_col + 1 > _numcols)) {
            scrollDisplayLeft();
        }
        else if (_text_dir == TEXT_DIR_RIGHT2LEFT && (_curs_col == 0)) {
            scrollDisplayRight();
        }
    }
    _ht.write(_curs_row * _numcols + _curs_col, value);

    // update cursor position according to direction
    if (_text_dir == TEXT_DIR_LEFT2RIGHT) {
        _curs_col = (_curs_col + 1) % _numcols;
    }
    else { // _text_dir = TEXT_DIR_RIGHT2LEFT
        _curs_col = (_curs_col + _numcols - 1) % _numcols;
    }
    // assume success
    return 1;
}

size_t LiquidCrystal7S::write(const uint8_t str[]) {
    register uint8_t i;

    for (i = 0; str[i]; i++)
        write(str[i]);

    // assume success
    return (size_t)i;
}