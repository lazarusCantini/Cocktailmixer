/* 
* AnalogDigitalConverter.cpp
*
* Created: 18.06.2018 18:11:34
* Author: Bastian Reul
*/


#include "AnalogDigitalConverter.h"



// default constructor
AnalogDigitalConverter::AnalogDigitalConverter(char PublicPort, uint8_t Public_Nummer_Pin)
{
	setze_Port(PublicPort);
	setze_PinNummer(Public_Nummer_Pin);
	setze_Richtung(true);
	initialisierePin();
	initialisiereADC();
} //AnalogDigitalConverter

void AnalogDigitalConverter::initialisiereADC()
{
   ADCA.CTRLB = ADC_RESOLUTION_8BIT_gc;
   ADCA.REFCTRL = ADC_REFSEL_AREFB_gc;
   ADCA.PRESCALER = ADC_PRESCALER_DIV512_gc;
   ADCA.CTRLA = ADC_ENABLE_bm;
   ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;
}

unsigned int AnalogDigitalConverter::getValue()
{
		switch (lese_Port())
		{
			case 'A':
			if (lese_PinNummer() == 0)
			{
				ADCA.CH0.MUXCTRL &= ~(1<<3);
				ADCA.CH0.MUXCTRL &= ~(1<<4);
				ADCA.CH0.MUXCTRL &= ~(1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 1)
			{
				ADCA.CH0.MUXCTRL |= (1<<3);
				ADCA.CH0.MUXCTRL &= ~(1<<4);
				ADCA.CH0.MUXCTRL &= ~(1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 2)
			{
				ADCA.CH0.MUXCTRL &= ~(1<<3);
				ADCA.CH0.MUXCTRL |=  (1<<4);
				ADCA.CH0.MUXCTRL &= ~(1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 3)
			{
				ADCA.CH0.MUXCTRL |=  (1<<3);
				ADCA.CH0.MUXCTRL |=  (1<<4);
				ADCA.CH0.MUXCTRL &= ~(1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 4)
			{
				ADCA.CH0.MUXCTRL &= ~(1<<3);
				ADCA.CH0.MUXCTRL &= ~(1<<4);
				ADCA.CH0.MUXCTRL |=  (1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 5)
			{
				ADCA.CH0.MUXCTRL |=  (1<<3);
				ADCA.CH0.MUXCTRL &= ~(1<<4);
				ADCA.CH0.MUXCTRL |=  (1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 6)
			{
				ADCA.CH0.MUXCTRL &= ~(1<<3);
				ADCA.CH0.MUXCTRL |=  (1<<4);
				ADCA.CH0.MUXCTRL |=  (1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			if (lese_PinNummer() == 7)
			{
				ADCA.CH0.MUXCTRL |=  (1<<3);
				ADCA.CH0.MUXCTRL |=  (1<<4);
				ADCA.CH0.MUXCTRL |=  (1<<5);
				ADCA.CH0.MUXCTRL &= ~(1<<6);
			}
			break;
/*			//Port B
			case 'B':
			if (lese_PinNummer() == 0)
			{
				
				TCD0.CCA = private_DutyCycle*5.0;
			}
			if (lese_PinNummer() == 1)
			{
				TCD0.CCB = private_DutyCycle*5.0;
			}
			break;*/
		}	
	
	//ADCA.CH0.MUXCTRL = ()
	//Channel->MUXCTRL = (Pin << 3);
	//Channel->CTRL |= ADC_CH_START_bm; 
	ADCA.CH0.CTRL |= (1 << 7); //Hier wird die eingestellte AD Konvertierung angestoßen und nach beendigung im CH0RES gespeichert
	
	//_delay_ms(500);
	//return ADCA.CH0RES;
	while(!ADCA.CH0.INTFLAGS);
	ADCA.CH0.INTFLAGS = ADC_CH_CHIF_bm; 
	return ADCA.CH0RES;  
}

// default destructor
AnalogDigitalConverter::~AnalogDigitalConverter()
{
} //~AnalogDigitalConverter
