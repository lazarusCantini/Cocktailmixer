/* 
* PwmPin.cpp
*
* Created: 07.06.2018 12:14:57
* Author: Bastian Reul
*/


#include "PwmPin.h"

PwmPin::PwmPin(double Dutycycle, double Frequenz, char PublicPort, uint8_t Public_Nummer_Pin)
{
	//ctor
	setze_Port(PublicPort);
	setze_PinNummer(Public_Nummer_Pin);
	set_Dutycycle(Dutycycle);
	set_Frequenz(Frequenz);
	

	setze_Richtung(false);
	initialisierePin();
	initialisierePWMPin();
}

void PwmPin::set_Dutycycle(double DutyCycle)
{
	if (DutyCycle < 99.9)
	{
		private_DutyCycle = DutyCycle;
	} 
	else
	{
		private_DutyCycle = 100.0;
	}
	
		switch (lese_Port())
		{
			case 'C':		
			if (lese_PinNummer() == 0)
			{
				TCC0.CCA = private_DutyCycle*5.0;
			}
			if (lese_PinNummer() == 1)
			{
				TCC0.CCB = private_DutyCycle*5.0;
			}
			if (lese_PinNummer() == 2)
			{
				TCC0.CCC = private_DutyCycle*5.0;
			}
			if (lese_PinNummer() == 3)
			{
				TCC0.CCD = private_DutyCycle*5.0;
			}
			break;
			//Port D
			case 'D':		
			if (lese_PinNummer() == 0)
			{
				
				TCD0.CCA = private_DutyCycle*5.0;
			}
			if (lese_PinNummer() == 1)
			{
				TCD0.CCB = private_DutyCycle*5.0;
			}
			break;
		}
}

void PwmPin::set_Frequenz(double Frequenz)
{
	private_Frequenz = Frequenz;
}

void PwmPin::set_SlopeStyle(uint8_t SlopeStyle )
{
	private_SlopeStyle = SlopeStyle;
}

double PwmPin::get_Dutycycle()
{
	return private_DutyCycle;
}

double PwmPin::get_Frequenz()
{
	return private_Frequenz;
}

uint8_t PwmPin::get_SlopeStyle()
{
	return private_SlopeStyle;
}

void PwmPin::set_PWM_status(bool status)
{
	switch (lese_Port())
	{
		case 'C':
		if (lese_PinNummer() == 0)
		{
			if (status)
			{
				TCC0.CTRLB |= (1<<4); // Setze das CCAEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C0 aktivieren)
			} 
			else
			{
				TCC0.CTRLB &= ~(1<<4) ; // Lösche das CCAEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C0 deaktivieren)
			}
			
		}
		if (lese_PinNummer() == 1)
		{
			if (status)
			{
				TCC0.CTRLB |= (1<<5); // Setze das CCBEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C1 aktivieren)
			}
			else
			{
				TCC0.CTRLB &= ~(1<<5) ; // Lösche das CCBEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C1 deaktivieren)
			}
		}
		if (lese_PinNummer() == 2)
		{
			if (status)
			{
				TCC0.CTRLB |= (1<<6); // Setze das CCCEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C2 aktivieren)
			}
			else
			{
				TCC0.CTRLB &= ~(1<<6) ; // Lösche das CCCEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C2 deaktivieren)
			}
		}
		if (lese_PinNummer() == 3)
		{
			if (status)
			{
				TCC0.CTRLB |= (1<<7); // Setze das CCDEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C3 aktivieren)
			}
			else
			{
				TCC0.CTRLB &= ~(1<<7) ; // Lösche das CCDEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin C3 deaktivieren)
			}
		}
		break;
		
		case 'D':
		if (lese_PinNummer() == 0)
		{
			if (status)
			{
				TCD0.CTRLB |= (1<<4); // Setze das CCAEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin D0 aktivieren)
			} 
			else
			{
				TCD0.CTRLB &= ~(1<<4) ; // Lösche das CCAEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin D0 deaktivieren)
			}
			
		}
		if (lese_PinNummer() == 1)
		{
			if (status)
			{
				TCD0.CTRLB |= (1<<5); // Setze das CCBEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin D1 aktivieren)
			}
			else
			{
				TCD0.CTRLB &= ~(1<<5) ; // Lösche das CCBEN Bit des CTRLB Registers. XMEGA A [MANUAL] S.164 (PWM an Pin D1 deaktivieren)
			}
		}
		break;
	}	
}

void PwmPin::initialisierePWMPin()
{
	//Atmel DAtenbatt
	//S.161 Das PER Register bestimmt die PWM Auflösung. Minimum 2 Bits-> .PER = 0x0003    Maximum -> 16Bits: .PER = 0xFFFF
	/*Frequenz der PWM:
						Fpwm=		CPUfrequenz
								------------------
						         Prescaler(Per + 1)   //Per als einfacher Dezimalwert
	
	CCA repräsentiert in Relation zur PER Angabe die PulsBreite.	PER=0xFFFF CCA 0x8888 = 50%
																	PER=0x8888 CCA 0x4444 = 50%
																	PER=0xFFFF CCA 0x4444 = 25%
	*/	
	switch (lese_Port())
	{
	case 'C':	
				PORTC.INTCTRL	= PORT_INT0LVL_LO_gc | PORT_INT1LVL_LO_gc; //Setze die InterruptLevels des Ports
				TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;  //Teiler von 265 und PER von 124 ergibt 1kHz Frequenz Habe Die Frequenz auf ca 120Hz gesenkt, dadurch fahren die Fader bei einer wesentlich geringeren PWM los (ca 80% bei 8Volt)
				TCC0.CTRLB = TC_WGMODE_SS_gc;		//Die Frequenz für die PWM gelten für alle Pins an Port C.
				TCC0.PER = 500;
				break;
	case 'D':		
				PORTD.INTCTRL	= PORT_INT0LVL_LO_gc | PORT_INT1LVL_LO_gc; //Setze die InterruptLevels des Ports
				TCD0.CTRLA = TC_CLKSEL_DIV1024_gc;  //Teiler von 265 und PER von 124 ergibt 1kHz Frequenz
				TCD0.CTRLB = TC_WGMODE_SS_gc;		//Die Frequenz für die PWM gelten für alle Pins an Port C.
				TCD0.PER = 500;
				break;
	}
	

}


// default destructor
PwmPin::~PwmPin()
{
} //~PwmPin
