//-------------------------------------------------------------------
// gs_gv.cpp
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

#include "gs.h"
#include <dht11.h>

dht11 *DHT = new dht11();

int dht_status = NOERR;
int tmode = TC;
int tmpF_off = 2;   // temp correction offset in F
int tmpC_off = 2;   // temp correction offset in C
int hum_off = 5;    // humidity correction offset

// Values set by data acquisition section. Conversions and scaling
// applied by data acquisition.
int curr_temp;
int curr_humid;
int curr_moist;
int curr_light;

// Setpoint values supplied by control host, these are default values just
// to give GS something to work with initially.
int maxhum   = 80;  // %RH
int minhum   = 40;  // %RH
int maxlite  = 90;  // rel. illum.
int minlite  = 20;  // rel. illum.
int maxmoist = 70;  // % (est)
int minmoist = 30;  // % (est)
int maxtemp  = 29;  // 85F
int mintemp  = 21;  // 70F

// Cal values derived from measurements, used to set input ranges
int cal_moist_min = 50;
int cal_moist_max = 500;
int cal_light_min = 50;
int cal_light_max = 500;

// Relay control variables
int rystate[2] = {0, 0};
int rylast[2] = {0, 0};
int rymap[2];
int rynum = 0;
