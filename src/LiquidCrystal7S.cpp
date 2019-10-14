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

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

void LiquidCrystal7S::initLCD()
{
    ht->begin();
    
    ht->sendCommand(HT1621::RC256K);
    ht->sendCommand(HT1621::BIAS_THIRD_4_COM);
    ht->sendCommand(HT1621::SYS_EN);
    ht->sendCommand(HT1621::LCD_ON);
}

LiquidCrystal7S::LiquidCrystal7S(uint8_t ss, uint8_t rw, uint8_t data) : _ss_pin(ss), _r_pin(rw), _w_pin(rw), _data_pin(data) {
    ht = new HT1621(_ss_pin, _r_pin, _data_pin);
    
    initLCD();
}

LiquidCrystal7S::LiquidCrystal7S(uint8_t ss, uint8_t r, uint8_t w, uint8_t data) : _ss_pin(ss), _r_pin(r), _w_pin(w), _data_pin(data) {
    ht = new HT1621(_ss_pin, _r_pin, _data_pin);

    initLCD();
}

void LiquidCrystal7S::begin(uint8_t cols, uint8_t lines) {
    _numcols = cols;
    _numrows = lines;
    _text_dir = TEXT_DIR_LEFT2RIGHT;
    _autoscroll = false;
    
    clear();
}

/********** high level commands, for the user! */
void LiquidCrystal7S::clear()
{
    register uint8_t i;
    
    for (i=0; i< HT1621_MAX_ADDR; i++)
        ht->write(i, 0);
    
    home();
}

void LiquidCrystal7S::scrollDisplayLeft(void) {
    register uint8_t i, j;
    register uint8_t saveFirst;
    
    _curs_col = (_curs_col + _numcols - 1) % _numcols; // move cursor right
    
    for(i=0; i<_numrows; i++) {
        saveFirst = ht->read(i*_numcols);
        for(j=_numcols-1; j>0; j--)
            ht->write(i*_numcols+j, ht->read(i*_numcols+j+1));
        ht->write((i+1)*_numcols-1, saveFirst);
    }
}

void LiquidCrystal7S::scrollDisplayRight(void) {
    register uint8_t i, j;
    register uint8_t saveLast;
    
    _curs_col = (_curs_col + 1) % _numcols; // move cursor right
    
    for(i=0; i<_numrows; i++) {
        saveLast = ht->read((i+1)*_numcols-1);
        for(j=1; j<_numcols; j++)
            ht->write(i*_numcols+j, ht->read(i*_numcols+j-1));
        ht->write(i*_numcols, saveLast);
    }
}
                      
size_t LiquidCrystal7S::write(uint8_t value) {
    if(_autoscroll)
        if(_text_dir == TEXT_DIR_LEFT2RIGHT && (_curs_col+1>_numcols))
            scrollDisplayLeft();
        else
            if(_text_dir == TEXT_DIR_RIGHT2LEFT && (_curs_col==0))
                scrollDisplayRight();
    
    ht->write(_curs_row*_numcols+_curs_col, value);
    
    // update cursor position according to direction
    if(_text_dir == TEXT_DIR_LEFT2RIGHT)
        _curs_col = (_curs_col + 1) % _numcols;
    else // _text_dir = TEXT_DIR_RIGHT2LEFT
        _curs_col = (_curs_col + _numcols - 1) % _numcols;
    
    // assume success
    return 1;
}

size_t LiquidCrystal7S::write(const uint8_t str[]) {
    register uint8_t i;

    if(_autoscroll)
        if(_text_dir == TEXT_DIR_LEFT2RIGHT && (_curs_col+1>_numcols))
            scrollDisplayLeft();
        else
            if(_text_dir == TEXT_DIR_RIGHT2LEFT && (_curs_col==0))
                scrollDisplayRight();
    
    // compute string length
    for(i=0; str[i]; i++);
    
    // print string
    ht->write(_curs_row*_numcols+_curs_col, (uint8_t *)str, i);
    
    // update cursor position according to direction
    if(_text_dir == TEXT_DIR_LEFT2RIGHT)
        _curs_col = (_curs_col + i) % _numcols;
    else { // _text_dir = TEXT_DIR_RIGHT2LEFT
        i %= _numcols;
        _curs_col = (_curs_col + _numcols - i) % _numcols;
    }
    
    // assume success
    return (size_t)i;
}