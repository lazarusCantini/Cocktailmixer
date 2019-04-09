/*
 * Bildschirmausgaben.cpp
 *
 * Created: 24.05.2018 10:42:47
 *  Author: Bastian Reul
 */ 

#include "lcd-routines.h"
#include <string.h>
#include <stdio.h> 
#include "StringOperationen.h"

//Ist dafür da, damit bei der LCD Initialisierung in der Main Methode nicht die lcd-routines in der main.cpp includiert werden muss
void Display_Init()
{
	lcd_init();
}

void BootBildschirm()
{
	lcd_clear();
	lcd_string("System faehrt");
	lcd_setcursor(0,2);
	lcd_string("hoch");
}

void IdleBildschirm()
{
	lcd_clear();
	lcd_setcursor(0,1);
	lcd_string("WHS-Sring 006");
	lcd_setcursor(0,2);
	lcd_string("Start druecken");
}

void Max_Fuellmaenge_beachten(unsigned int maxFuellmenge)
{
	lcd_clear();
	lcd_string("max. Fuellmenge von");
	lcd_setcursor(0,2);
	lcd_string(int_to_char_array(maxFuellmenge));
	lcd_string("mll beachten");
}


/*
	Gesammte Rezeptur
	eingeben XXX mll
	
Das XXX bezeichnet einen Platzhalter der in "Bildschirmausgabe_Rezeptur_einlesen_1" nicht beschrieben wird. Die Mengenangabe wird in
Bildschirmausgabe_Rezeptur_einlesen_2 immer wiederholt überschrieben. Der Rest bleibt stehen, damit der Bildschirm nicht flacktert
*/
void Bildschirmausgabe_Rezeptur_einlesen_1()
{
	lcd_clear();
	lcd_string("Rezeptur in");
	lcd_setcursor(0,2);
	lcd_string("Summe     mll");
}


void Bildschirmausgabe_Rezeptur_einlesen_2(unsigned int Menge)
{
	lcd_setcursor(9,2);
	if (Menge < 100)
	{
		lcd_string(" ");
	} 
	if (Menge < 10)
	{
		lcd_string(" ");
	}

	lcd_string(int_to_char_array(Menge));
	lcd_string(" mll");
}

void Debug_Start_gedrueckt()
{
	lcd_clear();
	lcd_string("Start wurde");
	lcd_setcursor(0,2);
	lcd_string("gedrueckt");
}

void Debug_Stop_gedrueckt()
{
	lcd_clear();
	lcd_string("Stop wurde");
	lcd_setcursor(0,2);
	lcd_string("gedrueckt");
}

void Debug_Pin_Nummer_nicht_initialisiert()
{
	lcd_setcursor(0,1);
	lcd_string("Err Pin Num");
}

void Debug_Port_Buchstabe_nicht_initialisiert()
{
	lcd_setcursor(0,2);
	lcd_string("Err Port Buchst");
}

void Debug_PWM_aktiviert()
{
	lcd_clear();
	lcd_string("PWM wurde");
	lcd_setcursor(0,2);
	lcd_string("akitviert");
}

void Debug_PWM_deaktiviert()
{
	lcd_clear();
	lcd_string("PWM wurde");
	lcd_setcursor(0,2);
	lcd_string("deakitviert");
}

void Debug_MotorTest_PMW_Status(double PWM_Prozent)
{
	// char buf[8];
	 
	//sprintf(buf,"%u.%u",(int)PWM_Prozent, (int)((PWM_Prozent - (int)PWM_Prozent) *100) );
	lcd_clear();
	lcd_string("Duty Cycle =");
	lcd_setcursor(0,2);
	lcd_string(double_to_char_array(PWM_Prozent));
}

void Debug_ADC_Wert_ausgeben(unsigned int ADC_Value)
{
	lcd_clear();
	lcd_string("ADC Wert");
	lcd_setcursor(0,2);
	lcd_string(int_to_char_array(ADC_Value));
}

void Debug_Abweichung_ausgeben(unsigned int abweichung)
{
	lcd_setcursor(0,1);
	lcd_string("Abweichung");
	lcd_setcursor(0,2);
	lcd_string(int_to_char_array(abweichung));
}

void Debug_Halt_wurde_erreicht()
{
	lcd_setcursor(0,1);
	lcd_string("Halt wurde");
	lcd_setcursor(0,2);
	lcd_string("erreicht.");	
}

void Debug_Rezept_wird_ausgegeben()
{
	lcd_setcursor(0,1);
	lcd_string("Rezept wird");
	lcd_setcursor(0,2);
	lcd_string("ausgegeben");
}

void Debug_Pumpe_NrX_wird_angesprochen(unsigned int x)
{
	lcd_clear();
	lcd_setcursor(0,1);
	lcd_string("Pumpe no ");
	lcd_setcursor(0,2);
	lcd_string(int_to_char_array(x));	
	lcd_setcursor(2,2);
	lcd_string(" angesprochen");
}

void Debug_UART_String_erkannt()
{
	lcd_setcursor(0,1);
	lcd_string("UART String");
	lcd_setcursor(0,2);
	lcd_string("erkannt");	
}