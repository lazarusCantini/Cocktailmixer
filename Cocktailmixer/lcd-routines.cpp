/*
 * lcd_routines.cpp
 *
 * Created: 21.02.2014 13:42:24
 *  Author: Bastian Reul
 */ 

// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// http://www.mikrocontroller.net/articles/HD44780
// http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/LCD-Ansteuerung
//
// Die Pinbelegung ist über defines in lcd-routines.h einstellbar

#include <avr/io.h>
#include "lcd-routines.h"
#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls
static void lcd_enable( void )
{
	PORTE_OUTSET = PIN1_bm;   // Enable auf 1 setzen
	_delay_us( LCD_ENABLE_US );  // kurze Pause
	PORTE_OUTCLR = PIN1_bm;    // Enable auf 0 setzen
}

////////////////////////////////////////////////////////////////////////////////
// Sendet eine 4-bit Ausgabeoperation an das LCD
static void lcd_out( uint8_t data )
{
	data &= 0xF0;                       // obere 4 Bit maskieren (niederwertiges Nibble löschen)
	
	//Jeder der 4 Bitpositionen des databits XXXX|0000 wird der auf den entsprechenden Pin & Pegel gesetzt
	//Datenleitung 7 (MSB) im ersten durchlauf, im zweiten: Bit no 3 des original Data-words
	if (data >= 128)
	{
		PORTR_OUTSET = PIN1_bm;
		data = data - 128;
	} 
	else
	{
		PORTR_OUTCLR = PIN1_bm;
	}
	
	//Datenleitung 6 im ersten Durchlauf, im zweiten: Bit no 2 des original Data-words
		if (data >= 64)
	{
		PORTR_OUTSET = PIN0_bm;
		data = data - 64;
	} 
	else
	{
		PORTR_OUTCLR = PIN0_bm;
	}
	
		//Datenleitung 5 im ersten Durchlauf, im zweiten: Bit no 1 des original Data-words
		if (data >= 32)
	{
		PORTE_OUTSET = PIN3_bm;
		data = data - 32;
	} 
	else
	{
		PORTE_OUTCLR = PIN3_bm;
	}
	
	//Datenleitung 4 im ersten Durchlauf, im zweiten: Bit no 0 des original Data-words
	if (data >= 16)
	{
		PORTE_OUTSET = PIN2_bm;
		data = data - 16;
	}
	else
	{
		PORTE_OUTCLR = PIN2_bm;
	}
	
	//Altes Verfahren - Funktioniert nur, wenn alle Datenpinns aufeinanderfolgend am selben Port hängen
	//LCD_PORT.OUT &= ~(0xF0>>(4-LCD_DB));    // Maske löschen
	//LCD_PORT.OUT |= (data>>(4-LCD_DB));     // Bits setzen
	lcd_enable();
}

////////////////////////////////////////////////////////////////////////////////
// Initialisierung: muss ganz am Anfang des Programms aufgerufen werden.
void lcd_init( void )
{
	//// verwendete Pins auf Ausgang schalten
	PORTR_DIRSET = PIN0_bm; //Register Select
	PORTR_DIRSET = PIN1_bm;	//LCD Enable
	PORTE_DIRSET = PIN0_bm; //Datenleitung 6
	PORTE_DIRSET = PIN1_bm; //Datenleitung 7
	PORTE_DIRSET = PIN2_bm; //Datenleitung 4
	PORTE_DIRSET = PIN3_bm; //Datenleitung 5
	
	// initial alle Ausgänge auf Null
	PORTR_OUTCLR = PIN0_bm;
	PORTR_OUTCLR = PIN1_bm;
	PORTE_OUTCLR = PIN0_bm;
	PORTE_OUTCLR = PIN1_bm;
	PORTE_OUTCLR = PIN2_bm;
	PORTE_OUTCLR = PIN3_bm;

	
	// warten auf die Bereitschaft des LCD
	_delay_ms( LCD_BOOTUP_MS );
	
	// Soft-Reset muss 3mal hintereinander gesendet werden zur Initialisierung
	lcd_out( LCD_SOFT_RESET );
	_delay_ms( LCD_SOFT_RESET_MS1 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS2 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS3 );
	
	// 4-bit Modus aktivieren
	lcd_out( LCD_SET_FUNCTION |
	LCD_FUNCTION_4BIT );
	_delay_ms( LCD_SET_4BITMODE_MS );
	
	// 4-bit Modus / 2 Zeilen / 5x7
	lcd_command( LCD_SET_FUNCTION |
	LCD_FUNCTION_4BIT |
	LCD_FUNCTION_2LINE |
	LCD_FUNCTION_5X7 );
	
	// Display ein / Cursor aus / Blinken aus
	lcd_command( LCD_SET_DISPLAY |
	LCD_DISPLAY_ON |
	LCD_CURSOR_OFF |
	LCD_BLINKING_OFF);
	
	// Cursor inkrement / kein Scrollen
	lcd_command( LCD_SET_ENTRY |
	LCD_ENTRY_INCREASE |
	LCD_ENTRY_NOSHIFT );
	
	lcd_clear();
}

////////////////////////////////////////////////////////////////////////////////
// Sendet ein Datenbyte an das LCD
void lcd_data( uint8_t data )
{
	PORTE_OUTSET = PIN0_bm;    // RS auf 1 setzen
	
	lcd_out( data );            // zuerst die oberen,
	lcd_out( data<<4 );         // dann die unteren 4 Bit senden
	
	_delay_us( LCD_WRITEDATA_US );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet einen Befehl an das LCD
void lcd_command( uint8_t data )
{
	PORTE_OUTCLR = PIN0_bm;    // RS auf 0 setzen
	
	lcd_out( data );             // zuerst die oberen,
	lcd_out( data<<4 );           // dann die unteren 4 Bit senden
	
	_delay_us( LCD_COMMAND_US );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl zur Löschung des Displays
void lcd_clear( void )
{
	lcd_command( LCD_CLEAR_DISPLAY );
	_delay_ms( LCD_CLEAR_DISPLAY_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl: Cursor Home
void lcd_home( void )
{
	lcd_command( LCD_CURSOR_HOME );
	_delay_ms( LCD_CURSOR_HOME_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (1..4)

void lcd_setcursor( uint8_t x, uint8_t y )
{
	uint8_t data;
	
	switch (y)
	{
		case 1:    // 1. Zeile
		data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
		break;
		
		case 2:    // 2. Zeile
		data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
		break;
		
		case 3:    // 3. Zeile
		data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
		break;
		
		case 4:    // 4. Zeile
		data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
		break;
		
		default:
		return;                                   // für den Fall einer falschen Zeile
	}
	
	lcd_command( data );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt einen String auf das LCD

void lcd_string( const char *data )
{
	while( *data != '\0' )
	lcd_data( *data++ );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt ein Zeichen in den Character Generator RAM

void lcd_generatechar( uint8_t code, const uint8_t *data )
{
	// Startposition des Zeichens einstellen
	lcd_command( LCD_SET_CGADR | (code<<3) );
	
	// Bitmuster übertragen
	for ( uint8_t i=0; i<8; i++ )
	{
		lcd_data( data[i] );
	}
}