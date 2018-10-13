/*
 * Potentiometer.h
 *
 * Created: 09.07.2018 11:51:32
 *  Author: Bastian Reul
 */ 


#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include "AnalogDigitalConverter.h"
#include "Bildschirmausgaben.h"
#include "Faderbewegung.h"
#include "LED.h"

extern volatile uint8_t ProgrammablaufStatus;
extern const uint8_t Sprungmarke_Fader_einlesen;
extern const uint8_t Sprungmarke_Rezept_ausgeben;
extern const uint8_t Sprungmarke_Start_Gedrueckt;
extern const uint8_t Sprungmarke_Bring_me_to_Idle_State;
extern volatile int max_Rezeptmenge;
extern AnalogDigitalConverter FaderADC_Array[6];
extern uint8_t OffsetArray[6];
extern volatile bool Kein_Offset_Abgleich_noetig;
extern volatile int Rezept_Array[6];
extern volatile bool StartTasterIgnorieren;
extern LED StartTasterLED;
extern LED StopTasterLED;

const uint8_t Potentiometer_MaxWert = 240;
const uint8_t Potentiometer_MinWert = 15;

void Rezeptur_einlesen();



#endif /* POTENTIOMETER_H_ */