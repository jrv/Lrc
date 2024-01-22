/*
  Lrc.h - Library for Lrc checking of a Modbus-ASCII hex string
  Created by Jaap Vermaas, Januari 21, 2023.
  Released into the public domain.
*/

#ifndef Lrc_h
#define Lrc_h

#include "Arduino.h"

class Lrc

{
  public:
    Lrc();
    void begin();
    uint8_t get(char value[], int l);
    uint8_t Char2Int8(char value[]);
    uint16_t Char2Int16(char value[]);
    char *Int2Char(char c[2], uint8_t value);
};
#endif
