/*
 * Schieberegister_Operationen.cpp
 *
 * Created: 04.07.2018 11:42:37
 *  Author: Bastian Reul
 */ 

#include "Schieberegister_Operationen.h"

void aktualisiere_alle_Gliederwerte()
{
	for (int i=0; i<6; i++)
	{
		Schubverband.aktualisiere_neuen_einzelWert(GliederVektor[i]);
	}
	
}