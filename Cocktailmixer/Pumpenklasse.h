/* 
* Pumpenklasse.h
*
* Created: 02.07.2018 14:27:11
* Author: Bastian Reul
*/


#ifndef __PUMPENKLASSE_H__
#define __PUMPENKLASSE_H__

#include "IC_74HC595.h"

class Pumpenklasse
{
//variables
public:
protected:
private:
			uint8_t pNummer_der_Pumpe;
			bool Pumpe_ist_aktiv;

//functions
public:
	Pumpenklasse(uint8_t nummer_der_Pumpe, IC_74HC595 *SchiebeIC);
	~Pumpenklasse();
	void setze_Pumpenstatus(bool status);
	void aktiviere_Pumpe();
	void deaktiviere_Pumpe();
	uint8_t get_Pumpennummer();
protected:
private:
	void setze_Pumpennummer(uint8_t nummer);
	IC_74HC595 *Zeiger_auf_SchiebeIC;
	volatile uint8_t Nummer_der_Pumpe_im_IC;

}; //Pumpenklasse

#endif //__PUMPENKLASSE_H__
