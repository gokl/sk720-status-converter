/*
 * Debug.h
 *
 *  Created on: 23.07.2015
 *      Author: gokl
 */

#ifndef DEBUG_H_
#define DEBUG_H_
#include "Arduino.h"

#include "Constants.h"
#include "SK720.h"

#ifdef DEBUG

#define initDebug() setupSerialCommunication()
#define debug(msg) serial.print(F(msg))
#define debugNum(number) serial.print(number, 10)
#define debugln(msg) serial.println(F(msg))
#define debuglnNum(number) serial.println(number, 10)

#pragma message ("Debug mode enabled. Enabling serial debug output on port PB3.")
#include "TinyDebugSerial.h"

void setupSerialCommunication();
void printLedState(LedState* ledState);
void printSystemState(SK720State state);
void printSingleLedMode(SingleLedMode state);

extern TinyDebugSerial serial;

#else

#define initDebug()
#define debug(msg)
#define debugNum(number)
#define debugln(msg)
#define debuglnNum(number)

#endif

#endif /* DEBUG_H_ */
