/*
 * Schieberegister_Operationen.h
 *
 * Created: 04.07.2018 11:42:22
 *  Author: Bastian Reul
 */ 


#ifndef SCHIEBEREGISTER_OPERATIONEN_H_
#define SCHIEBEREGISTER_OPERATIONEN_H_

#include "Schieberegister.h"
#include "IC_74HC595.h"

extern Schieberegister Schubverband;
extern IC_74HC595 GliederVektor[6];

void aktualisiere_alle_Gliederwerte();


#endif /* SCHIEBEREGISTER_OPERATIONEN_H_ */