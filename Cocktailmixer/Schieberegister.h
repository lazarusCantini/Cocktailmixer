#ifndef SCHIEBEREGISTER_H
#define SCHIEBEREGISTER_H
#include <stdint-gcc.h>
#include "IC_74HC595.h"
#include "Pin.h"

	extern Pin Shiftregister_Data_Input;
	extern Pin Shiftregister_Clock_Input;
	extern Pin Shiftregister_Master_Reset;
	extern Pin Shiftregister_Storage_Register_Clock_Input;
	extern Pin Shiftregister_Output_Enable;

class Schieberegister
{
	public:
	Schieberegister();
	void Setze_Soll_auf_Ist();
	void Setze_Ist_auf_Soll();
	volatile void aktualisiere_neuen_einzelWert(uint8_t Wert, uint8_t Kettenglied);
	void aktualisiere_neuen_einzelWert(IC_74HC595 Aktuelles_IC);
	void Ausgabe_IstWertDezimal();
	void Ausgabe_IstWertBinaer();
	void Ausgabe_SollWertBinaer();
	void Ausgabe_SollWertDezimal();
	void Aktualisiere_ist_gleich_Soll(bool Output_Active);
	void Output_Enable();
	void Output_Disable();
	void Reset_Shift_Register();
	void Schiebe_Datum_in_ShiftRegisterkette(uint8_t Datum);
	void Aktualisiere_Alle_Register();
	//virtual ~Schieberegister();


	protected:

	private:
	Pin private_DS;
	Pin private_SHCP;
	Pin private_MR;
	Pin private_STCP;
	Pin private_OE;
};

#endif // SCHIEBEREGISTER_H
