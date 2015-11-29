/**
 *
 */
#include "sk720_status_converter.h"

volatile boolean pinChanged = false;
volatile boolean wakeup = false;

SystemLedState systemLedState;
SK720Mode sk720Mode = SK720Mode_undefined;
SK720Mode sk720ModeBuffer[STATE_BUFFER_SIZE];
byte currentSk720Mode = 0;
boolean cycleVoltageMode = false;

void enterSleepMode() {
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode()
	;
}

void setupPinChangeInterrupts() {
	GIMSK |= _BV(PCIE);
	PCMSK |= _BV(PCINT1) | _BV(PCINT2);
	sei();
}

void setupWatchdogTimer() {
	MCUSR &= ~_BV(WDRF);
	WDTCR |= _BV(WDCE) | _BV(WDE);
	WDTCR = 0; // Timeout 16ms
	WDTCR |= _BV(WDIE);
}

void setuptInitialLedStates() {
	systemLedState = {
		{	SingleLedMode_off, GREEN_LED, false, 0UL, 0UL, 0UL},
		{	SingleLedMode_off, RED_LED, false, 0UL, 0UL, 0UL}
	};
	for (int i=0; i<STATE_BUFFER_SIZE; i++) {
		sk720ModeBuffer[i] = SK720Mode_undefined;
	}
}

void setup() {
	initDebug();
	setupChangeModePin();
	if (isCycleVoltageModeActive()) {
		cycleVoltageMode = true;
		sk720Mode = SK720Mode_off;
		debugln("Cycle mode activated");debug("Switching states every ");debugNum(CYCLE_MODE_DELAY_MS);debugln("ms.");
	} else {
		debugln("Normal mode activated");
		setupLEDPins();
		setuptInitialLedStates();
		setupWatchdogTimer();
		setupPinChangeInterrupts();
	}
	setupFastPWM();
	power_adc_disable();
	power_usi_disable();
}

void loop() {
	if (cycleVoltageMode == true) {
		outputSystemMode(sk720Mode);
#ifdef DEBUG
		debug("current state: ");
		printSystemMode(sk720Mode);
#endif
		sk720Mode = getNextSystemState(sk720Mode);
		delay(CYCLE_MODE_DELAY_MS);
	} else {
		if (wakeup == true) {
			wakeup = false;
			const unsigned long now = micros();
			if (pinChanged == true) {
				pinChanged = false;
				readLedStates(&systemLedState, now);
			}
			sk720ModeBuffer[currentSk720Mode] = inferSystemMode(&systemLedState,
					now);
#ifdef DEBUG
			SK720Mode oldState = sk720Mode;
#endif
			sk720Mode = getFilteredSk720Mode(sk720ModeBuffer, sk720Mode,
					sk720ModeBuffer[currentSk720Mode]);
#ifdef DEBUG
			if (sk720Mode != oldState) {
				debug("time ");
				debuglnNum(now);
				debug("redLed ");
				printSingleLedMode(systemLedState.red.mode);
				debug("greenLed ");
				printSingleLedMode(systemLedState.green.mode);
				debug("newState ");
				printSystemMode(sk720ModeBuffer[currentSk720Mode]);
				debug("filteredState ");
				printSystemState(sk720Mode);
				debug("filterIndex ");
				debuglnNum(currentSk720Mode);
				printLedState(&systemLedState.red);
				printLedState(&systemLedState.green);
				debugln("---");
			}
#endif

			if (currentSk720Mode == STATE_BUFFER_SIZE - 1) {
				currentSk720Mode = 0;
			} else {
				currentSk720Mode++;
			}
			outputSystemMode(sk720Mode);
		}
		enterSleepMode();
	}
}

/*
 * Watchdog timer ISR. Only used to wakeup loop()
 * for solid and off led state detection.
 */
ISR(WDT_vect) {
	wakeup = true;
}

/*
 * Pin change ISR.
 */
ISR(PCINT0_vect) {
	pinChanged = true;
	wakeup = true;
}

