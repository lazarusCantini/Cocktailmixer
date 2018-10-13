/*
 * Fader_Motor.h
 *
 * Created: 05.06.2018 16:30:37
 *  Author: Bastian Reul
 */ 
#include "Pin.h"
#include "IC_74HC595.h"
#include "PwmPin.h"

#ifndef FADER_MOTOR_H_
#define FADER_MOTOR_H_

/*
extern Pin Motor_Fader_1_Enable;
extern Pin Motor_Fader_2_Enable;
extern Pin Motor_Fader_3_Enable;
extern Pin Motor_Fader_4_Enable;
extern Pin Motor_Fader_5_Enable;
extern Pin Motor_Fader_6_Enable;*/
class Fader_Motor
{
	public:
	Fader_Motor(PwmPin *Enable_Pin);
	Fader_Motor(PwmPin *Enable_Pin, IC_74HC595 *SchiebeIC, uint8_t Position);
	void Disable_Motor();
	void Enable_Motor();
	void setze_Drehrichtung(bool positiv);
	bool get_Drehsinn();
	
	private:
	PwmPin *Zeiger_auf_Enable_Pin;
	IC_74HC595 *Zeiger_auf_SchiebeIC;
	volatile uint8_t Nummer_des_Motors_im_IC;	//Gibt an ob es sich um den linken oder rechten Motor des Treiberbausteins handelt
										//sprich ist der Motor an den Anschlüssen 1,2 oder 3,4 des L293 angeschlossen 
										//1 in der Variable bedeutet Anschlüsse 1,2     2 bedeutet 3,4
	bool Drehsinn;
};


#endif /* FADER_MOTOR_H_ */