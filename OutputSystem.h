/*
 * OutputSystem.h
 *
 *  Created on: 23.07.2015
 *      Author: gokl
 */

#ifndef OUTPUTSYSTEM_H_
#define OUTPUTSYSTEM_H_
#include "Arduino.h"

#include "Constants.h"
#include "SK720.h"

void setupFastPWM();
void setPwm(byte pwm);
void outputSystemMode(SK720Mode state);
SK720Mode getNextSystemState(SK720Mode currentState);

#endif /* OUTPUTSYSTEM_H_ */
