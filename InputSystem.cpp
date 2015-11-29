/*
 * Inputsystem.cpp
 *
 *  Created on: 23.07.2015
 *      Author: gokl
 */
#include "InputSystem.h"

#define isApproximately(number, target) \
	(number >= target - DELTA_MICROS) && \
	(number <= target + DELTA_MICROS)

#define activatePullUp(port) \
	digitalWrite(port, HIGH)

void setupLEDPins() {
	pinMode(GREEN_LED, INPUT);
	pinMode(RED_LED, INPUT);
	activatePullUp(GREEN_LED);
	activatePullUp(RED_LED);
}

void setupChangeModePin() {
	pinMode(CHANGE_MODE_PIN, INPUT);
	activatePullUp(CHANGE_MODE_PIN);
}

bool isCycleVoltageModeActive() {
	return digitalRead(CHANGE_MODE_PIN) == LOW;
}

void readSingleLedMode(LedState* ledState, const unsigned long now) {
	const int pinState = digitalRead(ledState->pin);
	if (pinState == LOW && ledState->state == false) {
		ledState->state = true;
		ledState->changeToHighTime = now;
		ledState->lastChangeTime = now;
	} else if (pinState == HIGH && ledState->state == true) {
		ledState->state = false;
		ledState->changeToLowTime = now;
		ledState->lastChangeTime = now;
	}
}

void readLedStates(SystemLedState* systemLedState, const unsigned long now) {
	readSingleLedMode(&systemLedState->red, now);
	readSingleLedMode(&systemLedState->green, now);
}

void inferSingleLedMode(LedState* ledState, const unsigned long now) {
	if ((now - ledState->lastChangeTime >= SOLID_MS)) {
		if (ledState->state == true) {
			ledState->mode = SingleLedMode_solid;
		} else {
			ledState->mode = SingleLedMode_off;
		}
	} else if ((ledState->state == false)) { // change to false -> we have the last HIGH period
		unsigned long highMicros = ledState->changeToLowTime
				- ledState->changeToHighTime;
		if (isApproximately(highMicros, SLOW_MICROS)) {
			ledState->mode = SingleLedMode_blinkingSlow;
		} else if (isApproximately(highMicros, FLICKERING_INVERSE_MICROS)) {
			ledState->mode = SingleLedMode_inverseFlickering;
		} else if (isApproximately(highMicros, FAST_MICROS)) {
			ledState->mode = SingleLedMode_blinkingFast;
		} else if (isApproximately(highMicros, FLICKERING_MICROS)) {
			ledState->mode = SingleLedMode_flickering;
		}
	}
}

SK720Mode inferSystemMode(SystemLedState* systemLedState,
		const unsigned long now) {
	inferSingleLedMode(&systemLedState->red, now);
	inferSingleLedMode(&systemLedState->green, now);
	SingleLedMode red = systemLedState->red.mode;
	SingleLedMode green = systemLedState->green.mode;
	SK720Mode state;
	if (red == SingleLedMode_off && green == SingleLedMode_off) {
		state = SK720Mode_off;
	} else if (red == SingleLedMode_off
			&& green == SingleLedMode_blinkingSlow) {
		state = SK720Mode_setupMode;
	} else if (red == SingleLedMode_off
			&& green == SingleLedMode_blinkingFast) {
		state = SK720Mode_usbFiletransfer;
	} else if (red == SingleLedMode_solid && green == SingleLedMode_off) {
		state = SK720Mode_flightModeInitializing;
	} else if (red == SingleLedMode_off && green == SingleLedMode_solid) {
		state = SK720Mode_flightModeReadyToFly;
	} else if (red == SingleLedMode_solid && green == SingleLedMode_solid) {
		state = SK720Mode_flightModeGpsReady;
	} else if (red == SingleLedMode_blinkingSlow
			&& green == SingleLedMode_solid) {
		state = SK720Mode_flightModeGpsActive;
	} else if (red == SingleLedMode_flickering
			&& green == SingleLedMode_inverseFlickering) {
		state = SK720Mode_flightModeHighVibrationWarning;
	} else if (red == SingleLedMode_blinkingFast
			&& green == SingleLedMode_off) {
		state = SK720Mode_errorState;
	} else {
		state = SK720Mode_undefined;
	}
	return state;
}

SK720Mode getFilteredSk720Mode(SK720Mode modeBuffer[], SK720Mode oldMode,
		SK720Mode newMode) {
	boolean allStatesEqual = true;
	for (int i = 0; i < STATE_BUFFER_SIZE - 1; i++) {
		allStatesEqual &= (modeBuffer[i] == modeBuffer[i + 1]);
	}
	if (allStatesEqual) {
		return newMode;
	} else {
		return oldMode;
	}
}

