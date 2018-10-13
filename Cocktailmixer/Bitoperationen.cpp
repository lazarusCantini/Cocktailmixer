#include <stdint.h>
#include <stdio.h>
#include <stdint-gcc.h>
#include "Schieberegister.h"

extern Schieberegister Schubverband;

volatile int Bit_Test(uint64_t *val, uint8_t bit) {
	uint64_t test_val = 0x01;    // dezimal 1 / binär 0000 0001 
	// Bit an entsprechende Pos. schieben 
	test_val = (test_val << bit);
	// 0=Bit nicht gesetzt; 1=Bit gesetzt 
	if ((*val & test_val) == 0)
	return 0;      // nicht gesetzt 
	else
	return 1;      // gesetzt 
}

volatile uint8_t Bit_Test(uint8_t val, uint8_t bit) {
	uint8_t test_val = 0x01;    /* dezimal 1 / binär 0000 0001 */
	/* Bit an entsprechende Pos. schieben */
	test_val = (test_val << bit);
	/* 0=Bit nicht gesetzt; 1=Bit gesetzt */
	if ((val & test_val) == 0)
	{return 0;}      /* nicht gesetzt */
	else
	{return 1; }     /* gesetzt */
}


void Bit_Set(uint64_t *val, uint8_t bit) {
	uint64_t test_val = 0x01;      /* dezimal 1 / binär 0000 0001 */
	/* Bit an entsprechende Pos. schieben */
	test_val = (test_val << bit);
	*val = (*val | test_val);     /* Bit an Pos. bit setzen */
}

void Bit_Clear(uint64_t *val, uint8_t bit) {
   uint64_t test_val = 0x01;        /* dezimal 1 / binär 0000 0001 */
   /* Bit an entsprechende Pos. schieben */
   test_val = (test_val << bit);
   *val = (*val & (~test_val));   /* Bit an Pos. bit löschen*/
}

volatile void Dez2Bin(uint64_t *Dezimalwert)
{
		volatile uint64_t test_val = 0x01;    /* dezimal 1 / binär 0000 0001 */

    for(volatile uint64_t i=0; i<48; i++)
    {

        /* 0=Bit nicht gesetzt; 1=Bit gesetzt */
		if ((*Dezimalwert & test_val) == 0)
        {
            Schubverband.Schiebe_Datum_in_ShiftRegisterkette(0);
			//Shiftregister_Data_Input.setze_Status(false);
        }
        else
        {
            Schubverband.Schiebe_Datum_in_ShiftRegisterkette(1);
			//Shiftregister_Data_Input.setze_Status(true);
        }
				/* Bit eine Position weiter schieben */
				test_val = (test_val << 1);
    }
}
