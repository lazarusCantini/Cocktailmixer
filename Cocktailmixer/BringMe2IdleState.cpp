/*
 * BringMe2IdleState.cpp
 *
 * Created: 26.06.2018 16:28:46
 *  Author: Bastian Reul
 */ 

#include "BringMe2IdleState.h"
#include "Faderbewegung.h"
#include "Bildschirmausgaben.h"



/*
Bringt das Programm von egal welcher Stelle im Programmcode
zum IDLE State
1: Pumpen aus
2: Fader nach unten und Motoren aus
3: Standardbildschirm (WHS Spring, drücken Sie Start)
4: Start Knopf LED an
5: Stop Knopf LED aus
6: LED Kranz am oberen Trichterrand läuft
*/

__attribute__((optimize(0)))
void bringMe2IdleState()
{
	deaktiviere_Pumpenarray(Pumpenarray);
	verfahre_alle_Fader_auf_gleichen_wert(15); //Original 15
	IdleBildschirm();
	
	StartTasterLED.schalte_ein();
	StopTasterLED.schalte_aus();
	for (int i=0; i++; i<6)
	{
		LEDKranz[i].schalte_aus();
	}
	aktualisiere_alle_Gliederwerte();
	Schubverband.Setze_Ist_auf_Soll();
	Schubverband.Aktualisiere_Alle_Register();
	Schubverband.Aktualisiere_ist_gleich_Soll(true);
	StartTasterIgnorieren = false;
}