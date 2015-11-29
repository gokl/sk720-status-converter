/*
 * Debug.cpp
 *
 *  Created on: 23.07.2015
 *      Author: gokl
 */

#include "Debug.h"

#ifdef DEBUG

TinyDebugSerial serial = TinyDebugSerial();

void setupSerialCommunication() {
	serial.begin(115200);
	debugln("SK720 Status Converter");
}

void printLedState(LedState* ledState) {
	debug("LED ");
	debuglnNum(ledState->pin);
	debuglnNum(ledState->lastChangeTime);
	debuglnNum(ledState->changeToHighTime);
	debuglnNum(ledState->changeToLowTime);
	debuglnNum(ledState->changeToLowTime - ledState->changeToHighTime);
}

void printSystemState(SK720State state) {
	switch (state) {
	case SK720State_undefined:
		debugln("undefined");
		break;

	case SK720State_off:
		debugln("off");
		break;

	case SK720State_setupMode:
		debugln("setupMode");
		break;

	case SK720State_usbFiletransfer:
		debugln("usbFiletransfer");
		break;

	case SK720State_flightModeInitializing:
		debugln("flightModeInitializing");
		break;

	case SK720State_flightModeReadyToFly:
		debugln("flightModeReadyToFly");
		break;

	case SK720State_flightModeGpsReady:
		debugln("flightModeGpsReady");
		break;

	case SK720State_flightModeGpsActive:
		debugln("flightModeGpsActive");
		break;

	case SK720State_flightModeHighVibrationWarning:
		debugln("flightModeHighVibrationWarning");
		break;

	case SK720State_errorState:
		debugln("errorState");
		break;

	case SK720State_firmwareUpdating:
		debugln("firmwareUpdating");
		break;

	default:
		debugln("default");
		break;
	}
}

void printSingleLedMode(SingleLedState state) {
	switch (state) {
	case SingleLedMode_off:
		debugln("off");
		break;

	case SingleLedMode_flickering:
		debugln("flickering");
		break;

	case SingleLedMode_blinkingFast:
		debugln("blinkingFast");
		break;

	case SingleLedMode_blinkingSlow:
		debugln("blinkingSlow");
		break;

	case SingleLedMode_inverseFlickering:
		debugln("inverseFlickering");
		break;

	case SingleLedMode_solid:
		debugln("solid");
		break;

	default:
		debugln("unknown");
		break;
	}
}
#endif

