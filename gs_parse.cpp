//-------------------------------------------------------------------
// gs_parse.cpp
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

#include "Arduino.h"
#include "gs.h"
#include "gs_gv.h"
#include "gs_parse.h"
#include "gs_send.h"
#include "gs_mapping.h"

// Collect incoming ASCII characters until a newline (linefeed)
// is encountered, or
void ParseCmd()
{
    int achan  = 0;
    int inchar = 0;
    int i      = 0;
    int slen   = 0;
    int ccnt   = 0;
    int ryst   = 0;

    char instr[MAXINSZ];    // Input buffer

    if (Serial.available() == 0) {
        return;
    }

    while (true) {
        if (Serial.available() > 0) {
            inchar = Serial.read();

            // read incoming command until '\n' (0x10) encountered
            if (inchar == 10) {
                instr[i] = 0;
                slen = i;
                break;
            }

            // prevent buffer overflow
            if (i >= MAXINSZ-1) {
                instr[i] = 0;
                slen = i;
                break;
            }

            instr[i] = (char) inchar;
            i++;
        }
    }

    switch (instr[0]) {
        case 'A':                                                   // AN:n:?
            if (instr[1] == 'N') {
                if (instr[2] == ':') {
                    achan = atoi((char *) &instr[3]);
                    if ((achan >= 0) && (achan < 6)) {
                        if (instr[4] == ':') {
                            if (instr[5] == '?') {
                                SendAnalog(achan);
                                break;
                            }
                        }
                    }
                    else {
                        SendErr(BADVAL);
                        break;
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        case 'G':
            if (instr[1] == 'T') {
                if (instr[2] == ':') {
                    if ((instr[3] == 'H') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // GT:HMX
                            SendHumMax();
                            break;
                        }
                        else if (instr[5] == 'N') {                 // GT:HMN
                            SendHumMin();
                            break;
                        }
                    }

                    if ((instr[3] == 'L') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // GT:LMX
                            SendLightMax();
                            break;
                        }
                        else if (instr[5] == 'N') {                 // GT:LMN
                            SendLightMin();
                            break;
                        }
                    }

                    if ((instr[3] == 'M') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // GT:MMX
                            SendMoistMax();
                            break;
                        }
                        else if (instr[5] == 'N') {                 // GT:MMN
                            SendMoistMin();
                            break;
                        }
                    }

                    if ((instr[3] == 'T') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // GT:TMX
                            SendTempMax();
                            break;
                        }
                        else if (instr[5] == 'N') {                 // GT:TMN
                            SendTempMin();
                            break;
                        }
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        case 'H':                                                   // HM:?
            if (instr[1] == 'M') {
                if (instr[2] == ':') {
                    if (instr[3] = '?') {
                        SendHum();
                        break;
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        case 'R':
            if (instr[1] == 'Y') {
                if (instr[2] == ':') {
                    if (instr[3] == 'A') {
                        if (instr[4] == ':') {
                            if (instr[5] == '1') {                  // RY:A:1
                                RyAll(1);
                                SendOK();
                                break;
                            }
                            else if (instr[5] == '0') {             // RY:A:0
                                RyAll(0);
                                SendOK();
                                break;
                            }
                        }
                    }
                    else {

                        rynum = atoi((char *) &instr[3]);           // RY:n:?
                        if ((rynum >= 0) && (rynum < 2)) {
                            // return relay state
                            if ((instr[4] == ':') && (instr[5] == '?')) {
                                SendRelay(rynum);
                                break;
                            }
                            else if (instr[4] == ':') {             // RY:n:1/0
                                // override relay state
                                if ((instr[5] == '0') || (instr[5] == '1')) {
                                    ryst = atoi((char *) &instr[5]);
                                    RySet(rynum, ryst);
                                    SendOK();
                                    break;
                                }
                                // disable mapping for specified relay
                                else if (instr[5] == 'N') {
                                    if (instr[6] == 'O') {
                                        if (instr[7] == 'N') {
                                            rymap[rynum] = MAP_NONE;
                                            SendOK();
                                        }
                                    }
                                }
                                // Assign relay to min or max for a given input
                                else if (instr[5] == 'H') {
                                    if (instr[6] == 'M') {
                                        if (instr[7] == 'N') {
                                            rymap[rynum] = MAP_HUMIDMIN;
                                            SendOK();
                                        }
                                        else if (instr[7] == 'X') {
                                            rymap[rynum] = MAP_HUMIDMAX;
                                            SendOK();
                                        }
                                        else {
                                            SendErr(BADCHAR);
                                        }
                                    }
                                    break;
                                }
                                else if (instr[5] == 'L') {
                                    if (instr[6] == 'M') {
                                        if (instr[7] == 'N') {
                                            rymap[rynum] = MAP_LIGHTMIN;
                                            SendOK();
                                        }
                                        else if (instr[7] == 'X') {
                                            rymap[rynum] = MAP_LIGHTMAX;
                                            SendOK();
                                        }
                                        else {
                                            SendErr(BADCHAR);
                                        }
                                    }
                                    break;
                                }
                                else if (instr[5] == 'M') {
                                    if (instr[6] == 'M') {
                                        if (instr[7] == 'N') {
                                            rymap[rynum] = MAP_MOISTMIN;
                                            SendOK();
                                        }
                                        else if (instr[7] == 'X') {
                                            rymap[rynum] = MAP_MOISTMAX;
                                            SendOK();
                                        }
                                        else {
                                            SendErr(BADCHAR);
                                        }
                                    }
                                    break;
                                }
                                else if (instr[5] == 'T') {
                                    if (instr[6] == 'M') {
                                        if (instr[7] == 'N') {
                                            rymap[rynum] = MAP_TEMPMIN;
                                            SendOK();
                                        }
                                        else if (instr[7] == 'X') {
                                            rymap[rynum] = MAP_TEMPMAX;
                                            SendOK();
                                        }
                                        else {
                                            SendErr(BADCHAR);
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        case 'S':
            if (instr[1] == 'T') {
                if (instr[2] == ':') {
                    if ((instr[3] == 'H') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // ST:HMX
                            if (instr[6] == ':') {
                                maxhum = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                        else if (instr[5] == 'N') {                 // ST:HMN
                            if (instr[6] == ':') {
                                minhum = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                    }

                    if ((instr[3] == 'L') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // ST:LMX
                            if (instr[6] == ':') {
                                maxlite = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                        else if (instr[5] == 'N') {                 // ST:LMN
                            if (instr[6] == ':') {
                                minlite = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                    }

                    if ((instr[3] == 'M') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // ST:MMX
                            if (instr[6] == ':') {
                                maxmoist = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                        else if (instr[5] == 'N') {                 // ST:MMN
                            if (instr[6] == ':') {
                                minmoist = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                    }

                    if ((instr[3] == 'T') && (instr[4] == 'M')) {
                        if (instr[5] == 'X') {                      // ST:TMX
                            if (instr[6] == ':') {
                                maxtemp = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                        else if (instr[5] == 'N') {                 // ST:TMN
                            if (instr[6] == ':') {
                                mintemp = CvtInt(instr,7,slen);
                                SendOK();
                                break;
                            }
                        }
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        case 'T':                                                   // TM:?
            if (instr[1] == 'M') {
                if (instr[2] == ':') {
                    if (instr[3] = '?') {
                        SendTemp();
                        break;
                    }
                }
            }
            SendErr(BADCHAR);
            break;
        default:
            SendErr(BADCHAR);
            break;
    }

}


// Convert ASCII digit character to numeric value by subtracting
// 0x30 ('0'), and mult by decade position (i.e. 1, 10, or 100).
// Will not convert numbers larger than 999.
int CvtInt(char *strval, int strt, int slen)
{
    int intval;

    if ((slen - strt) == 1) {
        intval = strval[strt] - '0';
    }
    else if ((slen - strt) == 2) {
        intval = ((strval[strt] - '0') * 10) + (strval[strt+1] - '0');
    }
    else if ((slen - strt) == 3) {
        intval = ((strval[strt] - '0') * 100) + ((strval[strt+1] - '0') * 10) + (strval[strt+2] - '0');
    }
    else
        intval = 0;

    return intval;
}


// Utility function to decode error and send appropriate
// response to host
void SendErr(int errtype)
{
    Serial.print("ER:");

    switch(errtype) {
        case TIMEOUT:
            Serial.print("TO");
            break;
        case BADCHAR:
            Serial.print("BC");
            break;
        case BADVAL:
            Serial.print("IV");
            break;
    }
    Serial.println();
    Serial.flush();
}

