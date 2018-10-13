/*
 * LED.h
 *
 * Created: 26.06.2018 16:30:52
 *  Author: Bastian Reul
 */ 


#ifndef LED_H_
#define LED_H_

#include "IC_74HC595.h"

class LED
{
	//variables
	public:
	protected:
	private:
		bool pZustand;
		IC_74HC595 *Zeiger_auf_SchiebeIC;
		volatile uint8_t Nummer_der_LED_im_IC;
	
	
	//functions
	public:
	LED();
	LED(uint8_t nummer_der_LED, IC_74HC595 *SchiebeIC);
	void setze_Zustand(bool Status);
	void schalte_ein();
	void schalte_aus();
	void aendere_Zustand();
	bool lese_Zustand();

	//virtual ~Pin();

	protected:

	private:


};



#endif /* LED_H_ */