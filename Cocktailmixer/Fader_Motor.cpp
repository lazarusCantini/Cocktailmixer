/*
 * Fader_Motor.cpp
 *
 * Created: 05.06.2018 16:30:05
 *  Author: Bastian Reul
 */ 

#include "Fader_Motor.h"
#include "Pin.h"
#include "IC_74HC595.h"

Fader_Motor::Fader_Motor(PwmPin *Enable_Pin)
{
	//ctor
	Zeiger_auf_Enable_Pin = Enable_Pin;

}

Fader_Motor::Fader_Motor(PwmPin *Enable_Pin, IC_74HC595 *SchiebeIC, uint8_t Position)
{
	//ctor
	Zeiger_auf_Enable_Pin = Enable_Pin;
	Zeiger_auf_SchiebeIC = SchiebeIC;
	Nummer_des_Motors_im_IC = Position;
	setze_Drehrichtung(true);
}

void Fader_Motor::Disable_Motor()
{
	 //funktioniert: Motor_Fader_1_Enable.setze_Status(false);
	 
	Zeiger_auf_Enable_Pin->set_PWM_status(false);
	
}

void Fader_Motor::Enable_Motor()
{
	Zeiger_auf_Enable_Pin->set_PWM_status(true);
	
}

bool Fader_Motor::get_Drehsinn()
{
	return Drehsinn;
}

void Fader_Motor::setze_Drehrichtung(bool positiv)
{
	if (Nummer_des_Motors_im_IC == 1)
	{
		if (positiv)
		{
			this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b10000000);
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00100000);
		}
		else
		{
			this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00100000);
			Zeiger_auf_SchiebeIC->Bits_loeschen(0b10000000);
		}
	}
	if (Nummer_des_Motors_im_IC == 2)
	{
		if (positiv)
		{
			this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00001000); 
			this->Zeiger_auf_SchiebeIC->Bits_loeschen(0b00000010);
		}
		else
		{
			this->Zeiger_auf_SchiebeIC->Bits_hinzufuegen(0b00000010);
			Zeiger_auf_SchiebeIC->Bits_loeschen(0b00001000);
		}
	}
	Drehsinn = positiv;	 
}