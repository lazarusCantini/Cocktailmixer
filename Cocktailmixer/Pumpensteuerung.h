/*
 * Pumpensteuerung.h
 *
 * Created: 02.07.2018 14:25:00
 *  Author: Bastian Reul
 */ 



#ifndef PUMPENSTEUERUNG_H_
#define PUMPENSTEUERUNG_H_

#ifndef F_CPU
#define F_CPU 32000000UL				// CPU Takt
#endif

#include "Pumpenklasse.h"
#include "Bildschirmausgaben.h"
#include "Schieberegister_Operationen.h"
#include "LED.h"
#include <util/delay.h>

extern volatile int Rezept_Array[6];
extern Schieberegister Schubverband;
extern LED LEDKranz[6];


void deaktiviere_Pumpenarray(Pumpenklasse *Zeiger_auf_Pumpenarray);
void Rezeptur_ausgeben(Pumpenklasse *Zeiger_auf_Pumpenarray);




#endif /* PUMPENSTEUERUNG_H_ */