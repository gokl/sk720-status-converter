/*
 * Constants.h
 *
 *  Created on: 24.07.2015
 *      Author: gokl
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Enable debug output via serial on PIN 3
//#define DEBUG

// When in cycle mode switch between states in this time
#define CYCLE_MODE_DELAY_MS 15000UL

// Timings or the various modes of the SK720 LEDs
#define FLICKERING_MICROS 25000UL // 25ms high 375ms low
#define FLICKERING_INVERSE_MICROS 375000UL // 375ms high 25ms low
#define FAST_MICROS 100000UL // 100ms high and low
#define SLOW_MICROS 400000UL // 400ms high and low
// TODO: #define VERY_SLOW_MICROS ???UL (Usb ile transfer)
#define SOLID_MS 500000UL // after 500ms the led is solid

// approximative time matching
#define DELTA_MICROS 10000UL

// Max amount of calculated states before state is clear
// = SOLID_MS / 16ms Watchdog + SOLID_MS / 25ms fastest blink + 1
// = 53
#define STATE_BUFFER_SIZE 53

// 255 / max number of sk720 states (8)
#define PWM_MULTIPLICATOR 31

// Connect this pin to GND on startup to enable cycle mode
#define CHANGE_MODE_PIN 0

// Connect the SK720s green LED here
#define GREEN_LED 2

// Connect the SK720s red LED here
#define RED_LED 1

// Serial output port. Cannot change this here (need to edit tinydebugserial).
//#define SERIAL_OUT 3

// Pin for the PWM signal. Don't change it!
#define PWM_PIN 4

#endif /* CONSTANTS_H_ */
