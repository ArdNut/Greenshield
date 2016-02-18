//-------------------------------------------------------------------
// gs_gv.h
//
// Created for "Arduino in a Nutshell", 2015, J. M. Hughes
// Chapter 10
//
// Copyight 2015-2016 John M. Hughes
// O'Reilly appreciates, but does not require, attribution. An attribution
// usually includes the title, author, publisher, and ISBN. For example:
// "Arduino in a Nutshell, by John M. Hughes. Copyright 2016 O’Reilly
// Media, Inc., ISBN: 978-1-4919-2176-0.
//
// If you feel your use of code examples falls outside fair use or the
// permission given above, feel free to contact permissions@oreilly.com.
//-------------------------------------------------------------------

#ifndef GSHIELD_H
#define GSHIELD_H

#include <dht11.h>

extern dht11 *DHT;

extern int dht_status;
extern int tmode;
extern int tmpF_off;
extern int tmpC_off;
extern int hum_off;

extern int curr_temp;
extern int curr_humid;
extern int curr_moist;
extern int curr_light;

extern int maxhum;
extern int minhum;
extern int maxlite;
extern int minlite;
extern int maxmoist;
extern int minmoist;
extern int maxtemp;
extern int mintemp;

extern int cal_moist_min;
extern int cal_moist_max;
extern int cal_light_min;
extern int cal_light_max;

extern int rystate[2];
extern int rylast[2];
extern int rymap[2];
extern int rynum;

#endif
