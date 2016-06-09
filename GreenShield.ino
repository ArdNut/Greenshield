//-------------------------------------------------------------------
// GreenShield.ino
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
#include "gs_gv.h"
#include "gs_parse.h"
#include "gs_send.h"
#include "gs_mapping.h"
#include <dht11.h>

void setup()
{
    Serial.begin(9600);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    pinMode(RY1,  OUTPUT);
    pinMode(RY2,  OUTPUT);

    pinMode(TST1, INPUT);
    pinMode(TST2, INPUT);
    pinMode(TMODE, INPUT);

    // enable internal pull-ups
    digitalWrite(TST1, HIGH);
    digitalWrite(TST2, HIGH);
    digitalWrite(TMODE, HIGH);

    dht_status = NOERR;

    // Step through the status LEDs
    digitalWrite(LED1, HIGH);
    delay(150);
    digitalWrite(LED1, LOW);
    delay(150);
    digitalWrite(LED2, HIGH);
    delay(150);
    digitalWrite(LED2, LOW);
    delay(150);
    digitalWrite(LED3, HIGH);
    delay(150);
    digitalWrite(LED3, LOW);
    delay(150);
    digitalWrite(LED4, HIGH);
    delay(150);
    digitalWrite(LED4, LOW);

    // check dig input for temp scale
    if (digitalRead(TMODE) == 0) {
        tmode = TF;
    }

    // Initial data acq and readout (optional)
    ReadDHT();
    curr_temp  = ReadTemp();
    curr_humid = ReadHumidity();
    curr_moist = ReadMoisture();
    curr_light = ReadLight();

    if (digitalRead(TST1) == 0) {
        Serial.print("Current temperature: ");
        Serial.println(curr_temp);
        Serial.print("Current humidity   : ");
        Serial.println(curr_humid);
        Serial.print("Current moisture   : ");
        Serial.println(curr_moist);
        Serial.print("Current light level: ");
        Serial.println(curr_light);
    }

    if (digitalRead(TST2) == 0) {
        digitalWrite(RY1, HIGH);
        delay(200);
        digitalWrite(RY1, LOW);
        delay(200);
        digitalWrite(RY2, HIGH);
        delay(200);
        digitalWrite(RY2, LOW);
    }

    Serial.println("OK");
}


void loop()
{
    // check dig input for temp scale
    if (digitalRead(TMODE) == 0) {
        tmode = TF;
    }

    ReadDHT();
    ParseCmd();
    curr_temp  = ReadTemp();
    curr_humid = ReadHumidity();
    curr_moist = ReadMoisture();
    curr_light = ReadLight();

    ScanMap();
    RyUpdate();
}
