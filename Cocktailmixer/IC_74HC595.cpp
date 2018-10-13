#include "IC_74HC595.h"
#include <stdint-gcc.h>



IC_74HC595::IC_74HC595()
{
	//ctor

}
IC_74HC595::IC_74HC595(uint8_t Wert, uint8_t Glied)
{
	setze_Nummer(Glied);
	setzte_Wert(Wert);
}

void IC_74HC595::setze_Nummer(uint8_t Kettenglied)
{
	Nummer_in_Reihe = Kettenglied;
}

void IC_74HC595::setzte_Wert(uint8_t Wert)
{
	Wert_des_Bausteins = Wert;
}

uint8_t IC_74HC595::get_Wert()
{
	return Wert_des_Bausteins;
}

uint8_t IC_74HC595::get_Nummer()
{
	return Nummer_in_Reihe;
}

//Diese Funktion fügt die übergeben Bits dem Register hinzu, lässt schon bestehende Bits aber unangetastet
/*Beispiel		Vorheriger Wert im IC:			0b10101010
				Nach dem Funktionsaufruf
				Bits_hinzufuegen(0b00001111)	0b10101111
Dies wird erreicht durch eine Bitweise "oder" (|) Verknüpfung
*/
void IC_74HC595::Bits_hinzufuegen(uint8_t Wert)
{
	uint8_t Operativer_Wert = get_Wert();
	Operativer_Wert = (Operativer_Wert | Wert);
	setzte_Wert(Operativer_Wert);
}

//Diese Funktion entfernt die übergeben Bits des Register, lässt alle anderen aber unangetastet
/*Beispiel		Vorheriger Wert im IC:			0b10101010
				Nach dem Funktionsaufruf
				Bits_löschen(0b00001011)		0b10100000
Dies wird erreicht durch eine Bitweise "oder" (|) Verknüpfung
*/
void IC_74HC595::Bits_loeschen(uint8_t Wert)
{
	uint8_t Operativer_Wert = get_Wert();
	if (Wert >= 128) //falls im Übergebenen Wert das Bit 0bX0000000 gesetzt ist, dann lösche es
	{
		Operativer_Wert &= ~(1 << 7);
		Wert = Wert - 128;
	}
	if (Wert >= 64) 
	{
		Operativer_Wert &= ~(1 << 6);
		Wert = Wert - 64;
	}
	if (Wert >= 32)
	{
		Operativer_Wert &= ~(1 << 5);
		Wert = Wert - 32;
	}
	if (Wert >= 16)
	{
		Operativer_Wert &= ~(1 << 4);
		Wert = Wert - 16;
	}	
	if (Wert >= 8)
	{
		Operativer_Wert &= ~(1 << 3);
		Wert = Wert - 8;
	}	
	if (Wert >= 4)
	{
		Operativer_Wert &= ~(1 << 2);
		Wert = Wert - 4;
	}
	if (Wert >= 2)
	{
		Operativer_Wert &= ~(1 << 1);
		Wert = Wert - 2;
	}
	if (Wert >= 1)
	{
		Operativer_Wert &= ~(1 << 0);
	}
	setzte_Wert(Operativer_Wert);
}


/*
IC_74HC595::~IC_74HC595()
{
	//dtor
}
*/