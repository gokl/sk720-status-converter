/*
 * SK720.h
 *
 *  Created on: 24.07.2015
 *      Author: gokl
 */

#ifndef SK720_H_
#define SK720_H_

/**
 * The various states a Skookum SK720(BE) can be in.
 */
typedef enum SK720Mode {
	SK720Mode_undefined,
	SK720Mode_off,
	SK720Mode_setupMode,
	SK720Mode_usbFiletransfer,
	SK720Mode_flightModeInitializing,
	SK720Mode_flightModeReadyToFly,
	SK720Mode_flightModeGpsReady,
	SK720Mode_flightModeGpsActive,
	SK720Mode_flightModeHighVibrationWarning,
	SK720Mode_errorState
} SK720Mode;

/**
 * The various states a single LED of the SK720(BE) can be in.
 */
typedef enum SingleLedMode {
	SingleLedMode_off,
	SingleLedMode_flickering,
	SingleLedMode_blinkingFast,
	SingleLedMode_blinkingSlow,
	SingleLedMode_inverseFlickering,
	SingleLedMode_solid
} SingleLedMode;


typedef struct LedState {
	SingleLedMode mode;
	byte pin;
	boolean state;
	unsigned long lastChangeTime;
	unsigned long changeToHighTime;
	unsigned long changeToLowTime;
} LedState;

typedef struct SystemLedState {
	LedState green;
	LedState red;
} SystemLedState;

#endif /* SK720_H_ */
