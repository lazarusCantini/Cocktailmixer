/*
 * Pumpensteuerung.cpp
 *
 * Created: 02.07.2018 14:25:15
 *  Author: Bastian Reul
 */ 
#include "Pumpensteuerung.h"
#include "Pumpenklasse.h"

#define  mll_zu_milliseconds_Faktor  340 //Faktor durch Berechnen und ausprobieren herausgefunden


void deaktiviere_Pumpenarray(Pumpenklasse *Zeiger_auf_Pumpenarray)
{
	for (int i=0; i<6; i++)
	{
		Zeiger_auf_Pumpenarray[i].deaktiviere_Pumpe();
	}
}


void Rezeptur_ausgeben(Pumpenklasse *Zeiger_auf_Pumpenarray)
{
	for (unsigned int i=0; i<6; i++)
	{
		if (Rezept_Array[i] > 0)
		{
			Debug_Pumpe_NrX_wird_angesprochen(i);
			Zeiger_auf_Pumpenarray[i].aktiviere_Pumpe();
			LEDKranz[i].schalte_ein();
									aktualisiere_alle_Gliederwerte();
									Schubverband.Setze_Ist_auf_Soll();
									Schubverband.Aktualisiere_Alle_Register();
									Schubverband.Aktualisiere_ist_gleich_Soll(true);
			for (int j=0; j < Rezept_Array[i]; j++)
			{
				_delay_ms(mll_zu_milliseconds_Faktor); 
			}
			Zeiger_auf_Pumpenarray[i].deaktiviere_Pumpe();
			for (int j=0; j<6; j++ )
			{
				LEDKranz[j].schalte_aus();
			}
									aktualisiere_alle_Gliederwerte();
									Schubverband.Setze_Ist_auf_Soll();
									Schubverband.Aktualisiere_Alle_Register();
									Schubverband.Aktualisiere_ist_gleich_Soll(true);
		}
	}
}