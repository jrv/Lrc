#include "Arduino.h"
#include "Lrc.h"

Lrc::Lrc() {
}

void Lrc::begin() {
  
}

uint8_t Lrc::get(char value[], int l) {
  uint8_t lrc = 0;
  for (int i = 0; i < l-1; i = i + 2) {
    lrc -= Char2Int8(&value[i]);
  }
  return lrc;
}

uint8_t Lrc::Char2Int8(char value[2]) {
  char c1 = value[0];
  uint8_t highBits = (c1 > '9')?(c1-55):(c1-48);
  char c2 = value[1];
  uint8_t lowBits = (c2 > '9')?(c2-55):(c2-48);
  return (highBits << 4 | lowBits);
}

uint16_t Lrc::Char2Int16(char value[4]) {
  uint16_t res = 0;
	char c;
	uint16_t bits;
	for (byte x=0; x<4; x++) {
    c = value[x];
		bits = (c > '9')?(c-55):(c-48);
		res = (res << 4 | bits);
	}
  return res;
}

char *Lrc::Int2Char(char c[2], uint8_t value) {
  uint8_t highBits = (value & 0xF0) >> 4;
  uint8_t lowBits = (value & 0x0F);
  c[0] = (highBits > 0x09)?(highBits+55):(highBits+48);
  c[1] = (lowBits > 0x09)?(lowBits+55):(lowBits+48);
  return c;
}
