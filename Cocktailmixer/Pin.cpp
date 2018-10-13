#include "Pin.h"
#include "Bildschirmausgaben.h"
#include <stdint-gcc.h>
#include <avr/io.h>

Pin::Pin()
{
	//Standardkonstruktor
}

Pin::Pin(char PublicPort, uint8_t Public_Nummer_Pin, bool Eingang)
{
	//ctor
	setze_Port(PublicPort);
	setze_PinNummer(Public_Nummer_Pin);
	setze_Richtung(Eingang);
	initialisierePin();  
}

void Pin::merke_status(bool status)
{
	status_intern = status;
}

void Pin::toggle_Pin()
{
	if (lese_status())
	{
		setze_Status(false);
	} 
	else
	{
		setze_Status(true);
	}
}

bool Pin::lese_status()
{
	return status_intern;
}

char Pin::lese_Port()
{
	return private_Port;
}

uint8_t Pin::lese_PinNummer()
{
	return private_Nummer_Pin;
}

void Pin::setze_Port(char PortBuchstabe)
{
	private_Port = PortBuchstabe;
}

void Pin::setze_PinNummer(uint8_t Pin_Nummer)
{
	private_Nummer_Pin = Pin_Nummer;
}

void Pin::setze_Richtung(bool is_Eingang)
{
	private_Eingang = is_Eingang;
}

void Pin::initialisierePin()
{
	if (private_Port == 'A')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN0_bm;} 
					else
					{PORTA_DIRSET = PIN0_bm;}
					break;
						
			case 1:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN1_bm;}
					else
					{PORTA_DIRSET = PIN1_bm;}
					break;
						
			case 2:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN2_bm;}
					else
					{PORTA_DIRSET = PIN2_bm;}
					break;
						
			case 3:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN3_bm;}
					else
					{PORTA_DIRSET = PIN3_bm;}
					break;
						
			case 4:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN4_bm;}
					else
					{PORTA_DIRSET = PIN4_bm;}
					break;
						
			case 5:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN5_bm;}
					else
					{PORTA_DIRSET = PIN5_bm;}
					break;
						
			case 6:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN6_bm;}
					else
					{PORTA_DIRSET = PIN6_bm;}
					break;
						
			case 7:	if (private_Eingang == true)
					{PORTA_DIRCLR = PIN7_bm;}
					else
					{PORTA_DIRSET = PIN7_bm;}
					break;
					
			default: Debug_Pin_Nummer_nicht_initialisiert();
					break;
						
		}
	}

	if (private_Port == 'B')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN0_bm;}
			else
			{PORTB_DIRSET = PIN0_bm;}
			break;
			
			case 1:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN1_bm;}
			else
			{PORTB_DIRSET = PIN1_bm;}
			break;
			
			case 2:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN2_bm;}
			else
			{PORTB_DIRSET = PIN2_bm;}
			break;
			
			case 3:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN3_bm;}
			else
			{PORTB_DIRSET = PIN3_bm;}
			break;
			
			case 4:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN4_bm;}
			else
			{PORTB_DIRSET = PIN4_bm;}
			break;
			
			case 5:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN5_bm;}
			else
			{PORTB_DIRSET = PIN5_bm;}
			break;
			
			case 6:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN6_bm;}
			else
			{PORTB_DIRSET = PIN6_bm;}
			break;
			
			case 7:	if (private_Eingang == true)
			{PORTB_DIRCLR = PIN7_bm;}
			else
			{PORTB_DIRSET = PIN7_bm;}
			break;
			
			default: Debug_Pin_Nummer_nicht_initialisiert();
			break;
			
		}
	}

	if (private_Port == 'C')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN0_bm;}
			else
			{PORTC_DIRSET = PIN0_bm;}
			break;
			
			case 1:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN1_bm;}
			else
			{PORTC_DIRSET = PIN1_bm;}
			break;
			
			case 2:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN2_bm;}
			else
			{PORTC_DIRSET = PIN2_bm;}
			break;
			
			case 3:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN3_bm;}
			else
			{PORTC_DIRSET = PIN3_bm;}
			break;
			
			case 4:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN4_bm;}
			else
			{PORTC_DIRSET = PIN4_bm;}
			break;
			
			case 5:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN5_bm;}
			else
			{PORTC_DIRSET = PIN5_bm;}
			break;
			
			case 6:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN6_bm;}
			else
			{PORTC_DIRSET = PIN6_bm;}
			break;
			
			case 7:	if (private_Eingang == true)
			{PORTC_DIRCLR = PIN7_bm;}
			else
			{PORTC_DIRSET = PIN7_bm;}
			break;
			
			default: Debug_Pin_Nummer_nicht_initialisiert();
			break;
			
		}
	}
	
	if (private_Port == 'D')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN0_bm;} 
					else
					{PORTD_DIRSET = PIN0_bm;}
					break;
						
			case 1:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN1_bm;}
					else
					{PORTD_DIRSET = PIN1_bm;}
					break;
						
			case 2:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN2_bm;}
					else
					{PORTD_DIRSET = PIN2_bm;}
					break;
						
			case 3:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN3_bm;}
					else
					{PORTD_DIRSET = PIN3_bm;}
					break;
						
			case 4:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN4_bm;}
					else
					{PORTD_DIRSET = PIN4_bm;}
					break;
						
			case 5:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN5_bm;}
					else
					{PORTD_DIRSET = PIN5_bm;}
					break;
						
			case 6:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN6_bm;}
					else
					{PORTD_DIRSET = PIN6_bm;}
					break;
						
			case 7:	if (private_Eingang == true)
					{PORTD_DIRCLR = PIN7_bm;}
					else
					{PORTD_DIRSET = PIN7_bm;}
					break;
					
			default: Debug_Pin_Nummer_nicht_initialisiert();
					break;
						
		}
	}

	if (private_Port == 'E')
	{
		switch(private_Nummer_Pin)
		{
			case 0:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN0_bm;}
			else
			{PORTE_DIRSET = PIN0_bm;}
			break;
			
			case 1:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN1_bm;}
			else
			{PORTE_DIRSET = PIN1_bm;}
			break;
			
			case 2:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN2_bm;}
			else
			{PORTE_DIRSET = PIN2_bm;}
			break;
			
			case 3:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN3_bm;}
			else
			{PORTE_DIRSET = PIN3_bm;}
			break;
			
			case 4:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN4_bm;}
			else
			{PORTE_DIRSET = PIN4_bm;}
			break;
			
			case 5:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN5_bm;}
			else
			{PORTE_DIRSET = PIN5_bm;}
			break;
			
			case 6:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN6_bm;}
			else
			{PORTE_DIRSET = PIN6_bm;}
			break;
			
			case 7:	if (private_Eingang == true)
			{PORTE_DIRCLR = PIN7_bm;}
			else
			{PORTE_DIRSET = PIN7_bm;}
			break;
			
			default: Debug_Pin_Nummer_nicht_initialisiert();
			break;
			
		}
	}

}

void Pin::setze_Status(bool Status)
{
		if (private_Port == 'A')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{PORTA_OUTSET = PIN0_bm;
				merke_status(true);}
				else
				{PORTA_OUTCLR = PIN0_bm;
				merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{PORTA_OUTSET = PIN1_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN1_bm;
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{PORTA_OUTSET = PIN2_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN2_bm;
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{PORTA_OUTSET = PIN3_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN3_bm;
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{PORTA_OUTSET = PIN4_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN4_bm;
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{PORTA_OUTSET = PIN5_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN5_bm;
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{PORTA_OUTSET = PIN6_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN6_bm;
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{PORTA_OUTSET = PIN7_bm;
					merke_status(true);}
				else
				{PORTA_OUTCLR = PIN7_bm;
					merke_status(false);}
				break;
				
				default: Debug_Pin_Nummer_nicht_initialisiert();
				break;
				
			}
		}

		if (private_Port == 'B')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{PORTB_OUTSET = PIN0_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN0_bm;
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{PORTB_OUTSET = PIN1_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN1_bm;
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{PORTB_OUTSET = PIN2_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN2_bm;
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{PORTB_OUTSET = PIN3_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN3_bm;
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{PORTB_OUTSET = PIN4_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN4_bm;
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{PORTB_OUTSET = PIN5_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN5_bm;
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{PORTB_OUTSET = PIN6_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN6_bm;
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{PORTB_OUTSET = PIN7_bm;
					merke_status(true);}
				else
				{PORTB_OUTCLR = PIN7_bm;
					merke_status(false);}
				break;
				
				default: Debug_Pin_Nummer_nicht_initialisiert();
				break;
				
			}
		}

		if (private_Port == 'C')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{PORTC_OUTSET = PIN0_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN0_bm;
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{PORTC_OUTSET = PIN1_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN1_bm;
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{PORTC_OUTSET = PIN2_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN2_bm;
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{PORTC_OUTSET = PIN3_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN3_bm;
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{PORTC_OUTSET = PIN4_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN4_bm;
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{PORTC_OUTSET = PIN5_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN5_bm;
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{PORTC_OUTSET = PIN6_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN6_bm;
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{PORTC_OUTSET = PIN7_bm;
					merke_status(true);}
				else
				{PORTC_OUTCLR = PIN7_bm;
					merke_status(false);}
				break;
				
				default: Debug_Pin_Nummer_nicht_initialisiert();
				break;
				
			}
		}
		
		if (private_Port == 'D')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{PORTD_OUTSET = PIN0_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN0_bm;
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{PORTD_OUTSET = PIN1_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN1_bm;
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{PORTD_OUTSET = PIN2_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN2_bm;
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{PORTD_OUTSET = PIN3_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN3_bm;
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{PORTD_OUTSET = PIN4_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN4_bm;
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{PORTD_OUTSET = PIN5_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN5_bm;
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{PORTD_OUTSET = PIN6_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN6_bm;
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{PORTD_OUTSET = PIN7_bm;
					merke_status(true);}
				else
				{PORTD_OUTCLR = PIN7_bm;
					merke_status(false);}
				break;
				
				default: Debug_Pin_Nummer_nicht_initialisiert();
				break;
				
			}
		}

		if (private_Port == 'E')
		{
			switch(private_Nummer_Pin)
			{
				case 0:	if (Status == true)
				{PORTE_OUTSET = PIN0_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN0_bm;
					merke_status(false);}
				break;
				
				case 1:	if (Status == true)
				{PORTE_OUTSET = PIN1_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN1_bm;
					merke_status(false);}
				break;
				
				case 2:	if (Status == true)
				{PORTE_OUTSET = PIN2_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN2_bm;
					merke_status(false);}
				break;
				
				case 3:	if (Status == true)
				{PORTE_OUTSET = PIN3_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN3_bm;
					merke_status(false);}
				break;
				
				case 4:	if (Status == true)
				{PORTE_OUTSET = PIN4_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN4_bm;
					merke_status(false);}
				break;
				
				case 5:	if (Status == true)
				{PORTE_OUTSET = PIN5_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN5_bm;
					merke_status(false);}
				break;
				
				case 6:	if (Status == true)
				{PORTE_OUTSET = PIN6_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN6_bm;
					merke_status(false);}
				break;
				
				case 7:	if (Status == true)
				{PORTE_OUTSET = PIN7_bm;
					merke_status(true);}
				else
				{PORTE_OUTCLR = PIN7_bm;}
				break;
				
				default: Debug_Pin_Nummer_nicht_initialisiert();
				break;
				
			}
		}
}
/*
Pin::~Pin()
{
	//dtor
}
*/