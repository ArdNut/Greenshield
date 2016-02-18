//-------------------------------------------------------------------
// gs_send.cpp
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
#include "gs_gv.h"
#include "gs_send.h"


void SendOK()
{
    Serial.println("OK");
}


void SendRelay(int rynum)
{
    Serial.print("RY:");
    Serial.print(rynum);
    Serial.print(":");
    Serial.print(rystate[rynum]);
    Serial.println();
}


void SendTemp()
{
    Serial.print("TM");
    Serial.print(":");
    Serial.print(curr_temp);
    Serial.println();
}


void SendHum()
{
    Serial.print("HM");
    Serial.print(":");
    Serial.print(curr_humid);
    Serial.println();
}


void SendAnalog(int chan)
{
    Serial.print("AN:");
    Serial.print(chan);
    Serial.print(":");
    Serial.print(analogRead(chan));
    Serial.println();
}


void SendHumMax()
{
    Serial.print("GT:HMX:");
    Serial.println(maxhum);
}


void SendHumMin()
{
    Serial.print("GT:HMN:");
    Serial.println(minhum);
}


void SendLightMax()
{
    Serial.print("GT:LMX:");
    Serial.println(maxlite);
}


void SendLightMin()
{
    Serial.print("GT:LMN:");
    Serial.println(minlite);
}


void SendMoistMax()
{
    Serial.print("GT:MMX:");
    Serial.println(maxmoist);
}


void SendMoistMin()
{
    Serial.print("GT:MMN:");
    Serial.println(minmoist);
}


void SendTempMax()
{
    Serial.print("GT:TMX:");
    Serial.println(maxtemp);
}


void SendTempMin()
{
    Serial.print("GT:TMN:");
    Serial.println(mintemp);
}
