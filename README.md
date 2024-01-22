# Lrc
Lrc Tools Library for Modbus-ASCII

This library contains some tests for Modbus-ASCII communication
Used on 2 x Arduino Uno with SN75176 RS485 chip

As seen on:
https://microcontrollerelectronics.com/sn75176-rs485-communications-between-two-arduinos/

Modbus-ASCII is just sending strings back and forth, but they contain a LRC checksum,
which can be extracted and checked with this library.

This code was written to test communication with ABL Emh1 Chargers
