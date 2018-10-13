/* 
* AnalogDigitalConverter.h
*
* Created: 18.06.2018 18:11:34
* Author: Bastian Reul
*/


#ifndef __ANALOGDIGITALCONVERTER_H__
#define __ANALOGDIGITALCONVERTER_H__

#ifndef F_CPU
#define F_CPU 32000000UL				// CPU Takt
#endif
#include <avr/io.h>
#include "Pin.h"
#include <util/delay.h>

class AnalogDigitalConverter : public Pin
{
//variables
public:
protected:
private:
	//Klassenvariablen um zu erkennen ob bereits ein konkretes Objekt des Entsprechenden ADC erstellt wurde
	static bool Converter_A_Exixts;
	static bool Converter_B_Exixts;

//functions
public:
	AnalogDigitalConverter(char PublicPort, uint8_t Public_Nummer_Pin);
	unsigned int getValue();
	~AnalogDigitalConverter();
protected:
private:
	//AnalogDigitalConverter( const AnalogDigitalConverter &c );
	void initialisiereADC();
	
	//AnalogDigitalConverter& operator=( const AnalogDigitalConverter &c );

}; //AnalogDigitalConverter

#endif //__ANALOGDIGITALCONVERTER_H__
