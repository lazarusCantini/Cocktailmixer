/*
 * uart_string_handling.cpp
 *
 * Created: 24.01.2018 16:15:56
 *  Author: Basti
 */ 

  #ifndef F_CPU
  #define F_CPU 32000000UL
  #endif

 #include "lcd-routines.h"
 #include <util/delay.h>
 #include "UART.h"
#include <stdlib.h>

 #define UART_MAXSTRLEN 60

 extern int uart_getraenke_wert[6];
extern char global_uart_string[UART_MAXSTRLEN + 1];
extern char *Letzter_Status;
/*
 int int_array_to_char(char *int_array, int laenge)
 {
	 char hilf;
	 int zahlenwert = 0;
	 int multiplikator = 1;
	 for (int i=laenge; i>0; i--)
	 {
		 hilf = char_array[i-1];
		 switch(hilf)
		 {
			 case '0':	zahlenwert = zahlenwert + (0 * multiplikator);
			 break;
			 case '1':	zahlenwert = zahlenwert + (1 * multiplikator);
			 break;
			 case '2':	zahlenwert = zahlenwert + (2 * multiplikator);
			 break;
			 case '3':	zahlenwert = zahlenwert + (3 * multiplikator);
			 break;
			 case '4':	zahlenwert = zahlenwert + (4 * multiplikator);
			 break;
			 case '5':	zahlenwert = zahlenwert + (5 * multiplikator);
			 break;
			 case '6':	zahlenwert = zahlenwert + (6 * multiplikator);
			 break;
			 case '7':	zahlenwert = zahlenwert + (7 * multiplikator);
			 break;
			 case '8':	zahlenwert = zahlenwert + (8 * multiplikator);
			 break;
			 case '9':	zahlenwert = zahlenwert + (9 * multiplikator);
			 break;

			 default:	lcd_clear();
			 lcd_home();
			 lcd_string("Zahl ungueltig");
			 _delay_ms(2000);
		 }
		 multiplikator = multiplikator * 10;
	 }
	 return zahlenwert;
 }
 */
 int char_array_to_int(char *char_array, int laenge)
 {
	char hilf;
	 int zahlenwert = 0;
	 int multiplikator = 1;
	 for (int i=laenge; i>0; i--)
	 {
	 hilf = char_array[i-1];
		 switch(hilf)
		 {
			 case '0':	zahlenwert = zahlenwert + (0 * multiplikator);
			 break;
			 case '1':	zahlenwert = zahlenwert + (1 * multiplikator);
			 break;
			 case '2':	zahlenwert = zahlenwert + (2 * multiplikator);
			 break;
			 case '3':	zahlenwert = zahlenwert + (3 * multiplikator);
			 break;
			 case '4':	zahlenwert = zahlenwert + (4 * multiplikator);
			 break;
			 case '5':	zahlenwert = zahlenwert + (5 * multiplikator);
			 break;
			 case '6':	zahlenwert = zahlenwert + (6 * multiplikator);
			 break;
			 case '7':	zahlenwert = zahlenwert + (7 * multiplikator);
			 break;
			 case '8':	zahlenwert = zahlenwert + (8 * multiplikator);
			 break;
			 case '9':	zahlenwert = zahlenwert + (9 * multiplikator);
			 break;

			 default:	Letzter_Status = "####Data_Invalid++++";
		 }
		 multiplikator = multiplikator * 10;
	 }
	 return zahlenwert;
 }

int* Rezeptur_berechnen(void)
 {
	char Prozentmenge[] = {'0','0','0','\n'};
	char* ArrayZeiger = Prozentmenge;	
	static int iProzentmengen[6];
	int position_in_string = 8;
	for (int i=0; i<6; i++)
	{
		for (int p=0; p<3; p++)
		{
			Prozentmenge[p] = global_uart_string[position_in_string];

			position_in_string = position_in_string +1;
		}
			iProzentmengen[i] = char_array_to_int(ArrayZeiger, 3);
			position_in_string = position_in_string + 5;
	}
	/*				 char test[4];
					 Send_UART("Zutat 1:");
					 itoa(iProzentmengen[0], test, 10);
					 Send_UART(test);
					 Send_UART("Zutat 2:");
					 itoa(iProzentmengen[1], test, 10);
					 Send_UART(test);
					 Send_UART("Zutat 3:");
					 itoa(iProzentmengen[2], test, 10);
					 Send_UART(test);
					 Send_UART("Zutat 4:");
					 itoa(iProzentmengen[3], test, 10);
					 Send_UART(test);
					 Send_UART("Zutat 5:");
					 itoa(iProzentmengen[4], test, 10);
					 Send_UART(test);
					 Send_UART("Zutat 6:");
					 itoa(iProzentmengen[5], test, 10);
					 Send_UART(test);

					 	int gesammt_Prozent = 0;
					 	for (int i=0; i<6; i++)
					 	{
						 	gesammt_Prozent = gesammt_Prozent + iProzentmengen[i];
					 	}
					 	if (gesammt_Prozent == 100)
					 	{
						 	Send_UART("####DATA_OK++++");
					 	}
					 	else
					 	{
						 	Send_UART("####DATA_INVALID++++");
					 	}
*/
	return iProzentmengen;
 }

