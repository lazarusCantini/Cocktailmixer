/*
 * LED.cpp
 *
 * Created: 26.06.2018 16:30:39
 *  Author: Bastian Reul
 */ 

#include "LED.h"

LED::LED(uint8_t nummer_der_LED, IC_74HC595 *SchiebeIC)
{
	Nummer_der_LED_im_IC = nummer_der_LED;
	Zeiger_auf_SchiebeIC = SchiebeIC;
	schalte_aus();
}

void LED::schalte_aus()
{	
	if (Nummer_der_LED_im_IC == 1)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b10000000);
	}
	if (Nummer_der_LED_im_IC == 2)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b01000000);
	}
	if (Nummer_der_LED_im_IC == 3)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00100000);
	}
	if (Nummer_der_LED_im_IC == 4)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00010000);
	}
	if (Nummer_der_LED_im_IC == 5)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00001000);
	}
	if (Nummer_der_LED_im_IC == 6)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000100);
	}
	if (Nummer_der_LED_im_IC == 7)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000010);
	}
	if (Nummer_der_LED_im_IC == 8)
	{
		this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000001);
	}
	pZustand = false;
}

void LED::schalte_ein()
{
	if (Nummer_der_LED_im_IC == 1)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b10000000);
	}
	if (Nummer_der_LED_im_IC == 2)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b01000000);
	}
	if (Nummer_der_LED_im_IC == 3)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00100000);
	}
	if (Nummer_der_LED_im_IC == 4)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00010000);
	}
	if (Nummer_der_LED_im_IC == 5)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00001000);
	}
	if (Nummer_der_LED_im_IC == 6)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000100);
	}
	if (Nummer_der_LED_im_IC == 7)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000010);
	}
	if (Nummer_der_LED_im_IC == 8)
	{
		this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000001);
	}
	pZustand = true;
}

void LED::aendere_Zustand()
{
	if (pZustand)
	{
		schalte_aus();
	} 
	else
	{
		schalte_ein();
	}
}
	
bool LED::lese_Zustand()
{
	return pZustand;
}
