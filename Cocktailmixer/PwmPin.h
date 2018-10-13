/* 
* PwmPin.h
*
* Created: 07.06.2018 12:14:57
* Author: Bastian Reul
*/


#ifndef __PWMPIN_H__
#define __PWMPIN_H__

#include "Pin.h"
#include <avr/io.h>

class PwmPin : public Pin
{
//variables
public:
protected:
private:

//functions
public:
	PwmPin(double Dutycycle, double Frequenz, char PublicPort, uint8_t Public_Nummer_Pin);
	void set_Dutycycle(double Dutycycle);
	void set_Frequenz(double Frequenz);
	void set_SlopeStyle(uint8_t SlopeStyle);
	double get_Dutycycle();
	double get_Frequenz();
	uint8_t get_SlopeStyle();
	void set_PWM_status(bool status);
	~PwmPin();
protected:
private:
	//PwmPin( const PwmPin &c );
	//PwmPin& operator=( const PwmPin &c );
	void initialisierePWMPin();
	
    double private_DutyCycle;
    double private_Frequenz;
    uint8_t private_SlopeStyle;

}; //PwmPin

#endif //__PWMPIN_H__
