/*
 * BringMe2IdleState.h
 *
 * Created: 26.06.2018 16:29:20
 *  Author: Bastian Reul
 */ 


#ifndef BRINGME2IDLESTATE_H_
#define BRINGME2IDLESTATE_H_

#include "Pumpenklasse.h"
#include "Pumpensteuerung.h"
#include "LED.h"

void bringMe2IdleState();

extern Pumpenklasse Pumpenarray[6];
extern LED StartTasterLED;
extern LED StopTasterLED;
extern LED LEDKranz[6];
extern volatile bool StartTasterIgnorieren;


#endif /* BRINGME2IDLESTATE_H_ */