/*
 * InputSystem.h
 *
 *  Created on: 24.07.2015
 *      Author: gokl
 */

#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_
#include "Arduino.h"

#include "Constants.h"
#include "SK720.h"
#include "Debug.h"

void setupLEDPins();
void setupChangeModePin();
bool isCycleVoltageModeActive();
void readSingleLedState(LedState* ledState, const unsigned long time);
void readLedStates(SystemLedState* systemLedState, const unsigned long time);
void inferSingleLedMode(LedState* ledState, const unsigned long time);
SK720Mode inferSystemMode(SystemLedState* systemLedState,
		const unsigned long time);
SK720Mode getFilteredSk720Mode(SK720Mode stateBuffer[], SK720Mode oldState,
		SK720Mode newState);

#endif /* INPUTSYSTEM_H_ */
