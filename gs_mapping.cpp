//-------------------------------------------------------------------
// gs_mapping.cpp
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

#include "Arduino.h"
#include "gs.h"
#include "gs_gv.h"
#include "gs_mapping.h"
#include <dht11.h>

void ReadDHT()
{
    int chk = DHT->readDHT(DHTPIN);
    switch (chk) {
        case DHT_OK:
            dht_status = NOERR;
            break;
        case DHT_CHKSUM_ERR:
            dht_status = CHKSUM;
            break;
        case DHT_TIMEOUT_ERR:
            dht_status = TIMEOUT;
            break;
        case DHT_INVALID_VAL:
            dht_status = BADVAL;
            break;
        default:
            dht_status = UNKERR;
            break;
    }
}

int ReadTemp()
{
    int rval = 0;

    // Get data from DHT22 sensor
    if (tmode == TF) {
        rval  = DHT->tmpF + tmpF_off;
    }
    else {
        rval  = DHT->tmpC + tmpC_off;
    }

    return rval;
}


int ReadHumidity()
{
    int rval = 0;

    // Get data from DHT22 sensor
    rval = DHT->humR + hum_off;

    return rval;
}


int ReadMoisture()
{
    int rval = 0;

    // Read moisture sensor analog input
    rval = analogRead(MPROBE);
    if (rval <= cal_moist_min)
        rval = 0;
    else if (rval >= cal_moist_max)
        rval = maxmoist;

    return rval;
}


int ReadLight()
{
    int rval = 0;

    // Read LDR sensor analog input
    rval = analogRead(LDRIN);
    if (rval <= cal_light_min)
        rval = 0;
    else if (rval >= cal_light_max)
        rval = maxlite;

    return rval;
}


int RyGet(int ry)
{
    return rystate[ry];
}


void RySet(int ry, int state)
{
    rystate[ry] = state;
}


void RyAll(int state)
{
    rystate[0] = state;
    rystate[1] = state;
}


void RyUpdate()
{
    if (rystate[0] == 1)
        digitalWrite(RY1, HIGH);
    if (rystate[0] == 0)
        digitalWrite(RY1, LOW);
    if (rystate[1] == 1)
        digitalWrite(RY2, HIGH);
    if (rystate[1] == 0)
        digitalWrite(RY2, LOW);
}

void LEDControl(int LEDidx)
{
    switch (LEDidx) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
}


// NOTE: There are no checks in this code to prevent multiple relays being
// mapped to the same operational mode.

// Each RY is mapped to one of 8 possible operational modes. Determine the
// mapping for a specific relay and see if the enable condition has been
// met. This is extensible to any reasonable number of relays.
void ScanMap()
{
    int rynew;

    for (int i = 0; i < MAXRY; i++) {
        if (rymap[i] != MAP_NONE) {
            switch (rymap[i]) {
                case MAP_TEMPMIN:
                    if (curr_temp < mintemp)   {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_TEMPMAX:
                    if (curr_temp > maxtemp)   {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_HUMIDMIN:
                    if (curr_humid < minhum)   {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_HUMIDMAX:
                    if (curr_humid > maxhum)   {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_MOISTMIN:
                    if (curr_moist < minmoist) {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_MOISTMAX:
                    if (curr_moist > maxmoist) {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_LIGHTMIN:
                    if (curr_light < minlite)  {rynew = 1;} else {rynew = 0;}
                    break;
                case MAP_LIGHTMAX:
                    if (curr_light > maxlite)  {rynew = 1;} else {rynew = 0;}
                    break;
                default:
                    // Do nothing
                    break;
            }

            // simple double-check debounce
            if (rylast[i] == rynew)
                RySet(i, rynew);

            rylast[i] = rynew;
        }
    }
}
