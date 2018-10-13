/*
 * Init_XMEGA.cpp
 *
 * Created: 18.08.2015 13:07:13
 *  Author: Administrator
 */ 

#include <avr/io.h>


void Clock_init(void)
{
	OSC.CTRL |= OSC_RC32MEN_bm;
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
}

void Init_XMEGA(void)
{
	Clock_init();
	
	//Setze Ausgänge
	
	//Multiplexer	
	//Mult_Port.DIR |= 0xFF;
	
	//LCD

	
	//Analog Digital Converter
	//Port A als Eingang setzen
	//PORTA.DIR = 0x00;
}