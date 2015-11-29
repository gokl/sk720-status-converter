/*
 * OutputSystem.cpp
 *
 *  Created on: 23.07.2015
 *      Author: gokl
 */

#include "OutputSystem.h"

void setupFastPWM() {
	// Enable 64 MHz PLL and use as source for Timer1
	PLLCSR = 1 << PCKE | 1 << PLLE;

	// Set up Timer/Counter1 for PWM output
	TIMSK &= ~_BV(OCIE1A);                     // Timer1 interrupts OFF
	TIMSK &= ~_BV(OCIE1B);                     // Timer1 interrupts OFF
	TIMSK &= ~_BV(TOIE1);                     // Timer1 interrupts OFF
	TCCR1 = 1 << CS10;               // 1:1 prescale
	GTCCR = 1 << PWM1B | 2 << COM1B0;  // PWM B, clear on match

	pinMode(PWM_PIN, OUTPUT);      // Enable PWM output pin
	setPwm(0);
}

void setPwm(byte pwm) {
	OCR1B = pwm;
}

void outputSystemMode(SK720Mode state) {
	byte pwm = 0;
	switch (state) {
	case SK720Mode_setupMode:
		pwm = 1;
		break;

	case SK720Mode_usbFiletransfer:
		pwm = 2;
		break;

	case SK720Mode_flightModeInitializing:
		pwm = 3;
		break;

	case SK720Mode_flightModeReadyToFly:
		pwm = 4;
		break;

	case SK720Mode_flightModeGpsReady:
		pwm = 5;
		break;

	case SK720Mode_flightModeGpsActive:
		pwm = 6;
		break;

	case SK720Mode_flightModeHighVibrationWarning:
		pwm = 7;
		break;

	case SK720Mode_errorState:
		pwm = 8;
		break;

	default: // undefined || SK720Mode_off
		pwm = 0;
		break;
	}
	setPwm(pwm * PWM_MULTIPLICATOR);
}

SK720Mode getNextSystemState(SK720Mode currentState) {
	SK720Mode newState = SK720Mode_off;
  switch (currentState) {
    case SK720Mode_setupMode:
      newState = SK720Mode_usbFiletransfer;
      break;

    case SK720Mode_usbFiletransfer:
      newState = SK720Mode_flightModeInitializing;
      break;

    case SK720Mode_flightModeInitializing:
      newState = SK720Mode_flightModeReadyToFly;
      break;

    case SK720Mode_flightModeReadyToFly:
      newState = SK720Mode_flightModeGpsReady;
      break;

    case SK720Mode_flightModeGpsReady:
      newState = SK720Mode_flightModeGpsActive;
      break;

    case SK720Mode_flightModeGpsActive:
      newState = SK720Mode_flightModeHighVibrationWarning;
      break;

    case SK720Mode_flightModeHighVibrationWarning:
      newState = SK720Mode_errorState;
      break;

    case SK720Mode_errorState:
      newState =SK720Mode_off;
      break;

    case SK720Mode_off:
      newState = SK720Mode_setupMode;
      break;
  }
  return newState;
}


