#ifndef BITOPERATIONEN_H
#define BITOPERATIONEN_H
#include <stdint-gcc.h>
volatile int Bit_Test(uint64_t *val, uint8_t bit);
volatile uint8_t Bit_Test(uint8_t val, uint8_t bit);
void Bit_Set(uint64_t *val, uint8_t bit);
void Bit_Clear(uint64_t *val, uint8_t bit);
volatile void Dez2Bin(uint64_t *Dezimalwert);

#endif // BITOPERATIONEN_H
