//-------------------------------------------------------------------
// gs_mapping.h
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

#ifndef GSMAP_H
#define GSMAP_H

void ReadDHT();
int  ReadTemp();
int  ReadHumidity();
int  ReadMoisture();
int  ReadLight();

int  RyGet(int ry);
void RySet(int ry, int state);
void RyAll(int state);
void RyUpdate();

void LEDControl(int LEDidx);
void ScanMap();

#endif
