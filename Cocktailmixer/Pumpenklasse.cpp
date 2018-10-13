/* 
* Pumpenklasse.cpp
*
* Created: 02.07.2018 14:27:10
* Author: Bastian Reul
*/


#include "Pumpenklasse.h"


// default constructor
Pumpenklasse::Pumpenklasse(uint8_t nummer_der_Pumpe, IC_74HC595 *SchiebeIC)
{
	pNummer_der_Pumpe = nummer_der_Pumpe;
	Zeiger_auf_SchiebeIC = SchiebeIC;
	Nummer_der_Pumpe_im_IC = nummer_der_Pumpe;
	deaktiviere_Pumpe();
} //Pumpenklasse

void Pumpenklasse::deaktiviere_Pumpe()
{
		if (Nummer_der_Pumpe_im_IC == 1)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b10000000);
		}
		if (Nummer_der_Pumpe_im_IC == 2)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b01000000);
		}
		if (Nummer_der_Pumpe_im_IC == 3)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00100000);
		}
		if (Nummer_der_Pumpe_im_IC == 4)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00010000);
		}
		if (Nummer_der_Pumpe_im_IC == 5)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00001000);
		}
		if (Nummer_der_Pumpe_im_IC == 6)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000100);
		}
		if (Nummer_der_Pumpe_im_IC == 7)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000010);
		}
		if (Nummer_der_Pumpe_im_IC == 8)
		{
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000001);
		}
}

void Pumpenklasse::aktiviere_Pumpe()
{
	if (Nummer_der_Pumpe_im_IC == 1)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b10000000);
	}
	if (Nummer_der_Pumpe_im_IC == 2)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b01000000);
	}
	if (Nummer_der_Pumpe_im_IC == 3)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00100000);
	}
	if (Nummer_der_Pumpe_im_IC == 4)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00010000);
	}
	if (Nummer_der_Pumpe_im_IC == 5)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00001000);
	}
	if (Nummer_der_Pumpe_im_IC == 6)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000100);
	}
	if (Nummer_der_Pumpe_im_IC == 7)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000010);
	}
	if (Nummer_der_Pumpe_im_IC == 8)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000001);
	}
}

void Pumpenklasse::setze_Pumpenstatus(bool status)
{
	if (status)
	{
		aktiviere_Pumpe();
	} 
	else
	{
		deaktiviere_Pumpe();
	}
}

uint8_t Pumpenklasse::get_Pumpennummer()
{
	return pNummer_der_Pumpe; 
}


// default destructor
Pumpenklasse::~Pumpenklasse()
{
} //~Pumpenklasse
