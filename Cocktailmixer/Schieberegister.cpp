#ifndef F_CPU
#define F_CPU 32000000UL				// CPU Takt
#endif

#define wait_long 300
#define wait_short 100

#include "Schieberegister.h"
#include "Bitoperationen.h"
#include "IC_74HC595.h"
#include "Pin.h"
#include <stdint-gcc.h>
#include <stdio.h>
#include <util/delay.h>
uint64_t Gesammtzustand_ist = 15000;
uint64_t Gesammtzustand_soll = 0;
uint64_t *Zeiger_Gesammtzustand_soll;
uint64_t *Zeiger_Gesammtzustand_ist;

extern IC_74HC595 Glied_1;
extern IC_74HC595 Glied_2;
extern IC_74HC595 Glied_3;
extern IC_74HC595 Glied_4;
extern IC_74HC595 Glied_5;
extern IC_74HC595 Glied_6;

Schieberegister::Schieberegister()
{
	//ctor
	Zeiger_Gesammtzustand_soll = &Gesammtzustand_soll;
	Zeiger_Gesammtzustand_ist = &Gesammtzustand_ist;

}

void Schieberegister::Setze_Soll_auf_Ist()
{

}

void Schieberegister::Setze_Ist_auf_Soll()
{
	Gesammtzustand_ist = Gesammtzustand_soll;
}

volatile void Schieberegister::aktualisiere_neuen_einzelWert(uint8_t Wert, uint8_t Kettenglied)
{
	for(int i=1; i<9; i++)
	{
		volatile uint8_t hilf = Bit_Test(Wert, i-1);
		if( hilf == 0b00000001)
		{
			Bit_Set(Zeiger_Gesammtzustand_soll, ((Kettenglied-1)*8+(i-1)));
		}
		else
		{
			Bit_Clear(Zeiger_Gesammtzustand_soll, ((Kettenglied-1)*8+(i-1)));
		}
	}
}

void Schieberegister::aktualisiere_neuen_einzelWert(IC_74HC595 Aktuelles_IC)
{
	aktualisiere_neuen_einzelWert(Aktuelles_IC.get_Wert(), Aktuelles_IC.get_Nummer());
}

void Schieberegister::Ausgabe_IstWertDezimal()
{
	//printf("Ist Wert Dezimal: %d\n" , Gesammtzustand_ist);
}

void Schieberegister::Ausgabe_SollWertDezimal()
{
	//printf("Soll Wert Dezimal: %d\n" , Gesammtzustand_soll);
}

void Schieberegister::Ausgabe_IstWertBinaer()
{
	//printf("Ist Wert Binaer: \n");
	//Dez2Bin(Gesammtzustand_ist);
	//printf("\n");
}

void Schieberegister::Ausgabe_SollWertBinaer()
{
	//printf("Soll Wert Binaer: \n");
	//Dez2Bin(Gesammtzustand_soll);
	//printf("\n");
}

void Schieberegister::Output_Enable()
{
	//PinD6 = Low ?Negierte Logik?
	Shiftregister_Output_Enable.setze_Status(false);
}

void Schieberegister::Output_Disable()
{
	//PinD6 = High
	Shiftregister_Output_Enable.setze_Status(true);
	
}

void Schieberegister::Reset_Shift_Register()
{
	//PinD7 Clock Leitung für Storage Register kann auf Low
	Shiftregister_Storage_Register_Clock_Input.setze_Status(false);
	//PinD4 Clock Leitung für Shift Register kann auf Low
	Shiftregister_Clock_Input.setze_Status(false);
	//PinD5 = Low Reset Line
	Shiftregister_Master_Reset.setze_Status(false);
	//Delay(x)
	_delay_us(wait_long);
	//PinD5 = High
	Shiftregister_Master_Reset.setze_Status(true);
}

void Schieberegister::Aktualisiere_Alle_Register()
{
	Dez2Bin(Zeiger_Gesammtzustand_ist);
}

void Schieberegister::Schiebe_Datum_in_ShiftRegisterkette(uint8_t Datum)
{
	if(Datum == 0)
	{
		//PinD3 = Low
		Shiftregister_Data_Input.setze_Status(false);
	}
	else
	{
		//PinD3 = High
		Shiftregister_Data_Input.setze_Status(true);
	}
	//Möglicherweie Delay
	_delay_us(wait_short);
	//PinD4 = High
	Shiftregister_Clock_Input.setze_Status(true);
	//Delay
	_delay_us(wait_long);
	//PinD4 = Low
	Shiftregister_Clock_Input.setze_Status(false);

}
//Hier wird das, was im Storage register aller 74HC595 Bausteinen steht, ins Storage Register geschrieben, und je nach Staus der AUsgang aktiviert oder deaktiviert
void Schieberegister::Aktualisiere_ist_gleich_Soll(bool Output_Active)
{
	//PinD6 = High
	Output_Disable();
	//PinD7 = High
	Shiftregister_Storage_Register_Clock_Input.setze_Status(true);
	//Delay
	_delay_us(wait_long);
	//PinD7 = Low
	Shiftregister_Storage_Register_Clock_Input.setze_Status(false);
	if(Output_Active)
	{
		//PinD6 = Low
		Output_Enable();
	}
	else
	{
		//PinD6 = High
		Output_Disable();
	}
	Setze_Ist_auf_Soll();
}

/*
Schieberegister::~Schieberegister()
{
	//dtor
}
*/