/*
 * Faderbewegung.h
 *
 * Created: 04.07.2018 10:49:00
 *  Author: Bastian Reul
 */ 


#ifndef FADERBEWEGUNG_H_
#define FADERBEWEGUNG_H_

#include "PwmPin.h"
#include "AnalogDigitalConverter.h"
#include "Fader_Motor.h"
#include "Schieberegister_Operationen.h"
#include "UART.h"

extern PwmPin Motor_Fader_Enable_Array[6];
extern Schieberegister Schubverband;
extern IC_74HC595 GliederVektor[6];
extern AnalogDigitalConverter FaderADC_Array[6];
extern bool Drehrichtung[6];
extern Fader_Motor Motor_Fader_Array[6];


uint8_t Regler(uint8_t abweichung, uint8_t Iteration);
void verfahre_Fader_auf_Wert(int *zeiger_auf_soll_array, PwmPin *Motor_Fader_Enable, AnalogDigitalConverter *FaderADC, Fader_Motor *Motor_Fader);
void verfahre_alle_Fader_auf_gleichen_wert(uint8_t soll);
double normiere_Fader_Wert_auf_Prozent(uint8_t FaderWert_uint8t);
uint8_t normiere_ProzentWert_auf_Fader_Wert(double Prozentwert);
void normiere_Array_auf_Fader_Wert(int *ProzentWerteArray);


#endif /* FADERBEWEGUNG_H_ */