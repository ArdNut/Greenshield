//-------------------------------------------------------------------
// gs.h
//
// Created for "Arduino: A Technical Reference", 2016, J. M. Hughes
// Chapter 10
//
// Copyight 2015-2016 John M. Hughes
// O'Reilly appreciates, but does not require, attribution. An attribution
// usually includes the title, author, publisher, and ISBN. For example:
// "Arduino: A Technical Reference, by John M. Hughes. Copyright 2016 O’Reilly
// Media, Inc., ISBN: 978-1-491-92176-0".
//
// If you feel your use of code examples falls outside fair use or the
// permission given above, feel free to contact permissions@oreilly.com.
//-------------------------------------------------------------------

#ifndef GSDEFS_H
#define GSDEFS_H

#define MAXINSZ         12      // input buffer size

#define TC              0       // Temp in degrees C
#define TF              1       // Temp in degrees F

#define NOERR           0       // Error codes
#define TIMEOUT         1
#define BADCHAR         2
#define BADVAL          3
#define CHKSUM          4
#define UNKERR          5

#define LED1            2       // LED pin definitions
#define LED2            3
#define LED3            4
#define LED4            5
#define RY1             6       // Relay pin definitions
#define RY2             7
#define DHTPIN          8       // DHT22 I/O pin

#define TST1            16      // (A2) Test pin 1 (show init readings)
#define TST2            17      // (A3) Test pin 2 (test relays)
#define TMODE           9       // Temp scale select

#define MPROBE          A0      // Moisture probe input
#define LDRIN           A1      // LDR input

#define MAXRY           2       // Maximum num of relays

#define MAP_NONE        0       // Mapping vectors
#define MAP_TEMPMIN     1
#define MAP_TEMPMAX     2
#define MAP_HUMIDMIN    3
#define MAP_HUMIDMAX    4
#define MAP_MOISTMIN    5
#define MAP_MOISTMAX    6
#define MAP_LIGHTMIN    7
#define MAP_LIGHTMAX    8

#endif
