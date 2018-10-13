/*
 * Potentiometer.cpp
 *
 * Created: 09.07.2018 11:51:43
 *  Author: Bastian Reul
 */ 

#include "Potentiometer.h"

//Solange sich der Programmablaufstatus auf 9 befindet, läuft eine endlosschleife die die Werte der Potentiometer ausliest und
//die Summer aller Werte auf dem Display ausgibt
__attribute__((optimize(0)))
//nicht so recht funktionierende Funktion
/*
void Rezeptur_einlesen()
{
	bool LED_Zustand_alt = true;
	bool LED_Zustand_soll = true;
	unsigned int Summe_Rezept = 0;
	Bildschirmausgabe_Rezeptur_einlesen_1();
	
	//Offset der fast auf Null stehenden Fader einlesen und für alle weiteren Iterationen abziehen
	if (!(Kein_Offset_Abgleich_noetig))
	{
		for (int j=0; j<6; j++)
		{
			OffsetArray[j] = FaderADC_Array[j].getValue();
		}
	}

	int hilf = 0;
 	while (ProgrammablaufStatus == Sprungmarke_Fader_einlesen)
	{
		Summe_Rezept = 0;
		for (int i=0; i<6; i++)
		{
			hilf = normiere_Fader_Wert_auf_Prozent(FaderADC_Array[i].getValue()-OffsetArray[i]);
			//hilf = FaderADC_Array[i].getValue()-OffsetArray[i];
			if (hilf < 0)
			{
				hilf = 0;
			}
			Summe_Rezept = Summe_Rezept + (double(hilf)/double(100)*double(max_Rezeptmenge)); //Gesammtsumme für Mengenprüfung und Displayausgabe
			Rezept_Array[i] = (double(hilf)/double(100)*double(max_Rezeptmenge)); // Wieviel mll tatsächlich von jeder Flasche verpumpt werden muss


		}
		Bildschirmausgabe_Rezeptur_einlesen_2(Summe_Rezept);
		StartTasterIgnorieren = false;
			if (Summe_Rezept <= max_Rezeptmenge)
			{
				LED_Zustand_soll = true;
				if (!(LED_Zustand_alt == LED_Zustand_soll))
				{
					StartTasterLED.schalte_ein();
					StopTasterLED.schalte_aus();
					aktualisiere_alle_Gliederwerte();
					Schubverband.Setze_Ist_auf_Soll();
					Schubverband.Aktualisiere_Alle_Register();
					Schubverband.Aktualisiere_ist_gleich_Soll(true);
					LED_Zustand_alt = StartTasterLED.lese_Zustand();
				}
			}
			else
			{
				LED_Zustand_soll = false;
				if (!(LED_Zustand_alt == LED_Zustand_soll))
				{
					StartTasterLED.schalte_aus();
					StopTasterLED.schalte_ein();
					aktualisiere_alle_Gliederwerte();
					Schubverband.Setze_Ist_auf_Soll();
					Schubverband.Aktualisiere_Alle_Register();
					Schubverband.Aktualisiere_ist_gleich_Soll(true);
					LED_Zustand_alt = StartTasterLED.lese_Zustand();
				}
			}
	}
	
	if (ProgrammablaufStatus != Sprungmarke_Bring_me_to_Idle_State)
	{
		if (Summe_Rezept <= max_Rezeptmenge)
		{
			ProgrammablaufStatus = Sprungmarke_Rezept_ausgeben;
		} 
		else
		{
			Kein_Offset_Abgleich_noetig = true;
			ProgrammablaufStatus = Sprungmarke_Start_Gedrueckt;
		}
	}
}
*/

//neue Version ohne Offset_Abgleich
void Rezeptur_einlesen()
{
	bool LED_Zustand_alt = true;
	bool LED_Zustand_soll = true;
	unsigned int Summe_Rezept = 0;
	Bildschirmausgabe_Rezeptur_einlesen_1();
	double DigitsJeMll = Potentiometer_MaxWert / max_Rezeptmenge;
	int Faderwert = 0;
	int rundungswert = 0;
	int Offsetbereinigt = 0;
	double NormierterWert = 0;
	int hilf = 0;
								const int Filterbreite = 5;
								double Filterwert = 0.0;
	while (ProgrammablaufStatus == Sprungmarke_Fader_einlesen)
	{
		Summe_Rezept = 0;
		for (int i=0; i<6; i++)
		{
		//	Rezept_Array[i] = round((FaderADC_Array[i].getValue()-Potentiometer_MinWert)*DigitsJeMll);

							Filterwert = 0.0;
							for (int j=0; j<Filterbreite; j++)
							{
								Filterwert = Filterwert + FaderADC_Array[i].getValue();
							}
							Faderwert = int(round(Filterwert/Filterbreite));
		
		
			//Faderwert = FaderADC_Array[i].getValue();
			Offsetbereinigt = Faderwert - Potentiometer_MinWert;
			NormierterWert = Offsetbereinigt / DigitsJeMll;
			rundungswert = round(NormierterWert);
			Rezept_Array[i] = rundungswert;
			
			
			if (Rezept_Array[i] < 4)
			{
				Rezept_Array[i] = 0;
			}
			Summe_Rezept = Summe_Rezept + Rezept_Array[i];
		}
		Bildschirmausgabe_Rezeptur_einlesen_2(Summe_Rezept);
		StartTasterIgnorieren = false;
		if (Summe_Rezept <= max_Rezeptmenge)
		{
			LED_Zustand_soll = true;
			if (!(LED_Zustand_alt == LED_Zustand_soll))
			{
				StartTasterLED.schalte_ein();
				StopTasterLED.schalte_aus();
				aktualisiere_alle_Gliederwerte();
				Schubverband.Setze_Ist_auf_Soll();
				Schubverband.Aktualisiere_Alle_Register();
				Schubverband.Aktualisiere_ist_gleich_Soll(true);
				LED_Zustand_alt = StartTasterLED.lese_Zustand();
			}
		}
		else
		{
			LED_Zustand_soll = false;
			if (!(LED_Zustand_alt == LED_Zustand_soll))
			{
				StartTasterLED.schalte_aus();
				StopTasterLED.schalte_ein();
				aktualisiere_alle_Gliederwerte();
				Schubverband.Setze_Ist_auf_Soll();
				Schubverband.Aktualisiere_Alle_Register();
				Schubverband.Aktualisiere_ist_gleich_Soll(true);
				LED_Zustand_alt = StartTasterLED.lese_Zustand();
			}
		}
	}
	
	if (ProgrammablaufStatus != Sprungmarke_Bring_me_to_Idle_State)
	{
		if (Summe_Rezept <= max_Rezeptmenge)
		{
			ProgrammablaufStatus = Sprungmarke_Rezept_ausgeben;
		}
		else
		{
			Kein_Offset_Abgleich_noetig = true;
			ProgrammablaufStatus = Sprungmarke_Start_Gedrueckt;
		}
	}
}