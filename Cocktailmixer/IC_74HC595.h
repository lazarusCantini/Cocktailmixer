#ifndef IC_74HC595_H
#define IC_74HC595_H
#include <stdint-gcc.h>

class IC_74HC595
{
	public:

	IC_74HC595();
	IC_74HC595(uint8_t Wert, uint8_t Glied);
	void setzte_Wert(uint8_t Wert);
	void setze_Nummer(uint8_t Kettenglied);
	uint8_t get_Wert();
	uint8_t get_Nummer();
	void Bits_hinzufuegen(uint8_t Wert);
	void Bits_loeschen(uint8_t Wert);

	//virtual ~IC_74HC595();

	protected:

	private:
	uint8_t Nummer_in_Reihe;
	uint8_t Wert_des_Bausteins;
};

#endif // IC_74HC595_H
