
 #ifndef F_CPU
 #define F_CPU 32000000UL
 #endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>




#define UART_MAXSTRLEN 60

extern volatile uint8_t global_uart_str_complete;
extern volatile char global_uart_string[UART_MAXSTRLEN + 1];
extern char *Letzter_Status;
// USART
volatile uint8_t uart_str_complete = 0;    // 1 .. String komplett empfangen
volatile uint8_t uart_str_count = 0;
volatile char uart_string[UART_MAXSTRLEN + 1] = "";
volatile uint8_t start_sequenz_counter = 0;
volatile uint8_t end_sequenz_counter = 0;
extern volatile uint8_t count_plus;
extern volatile uint8_t count_hash;
extern volatile int Rezept_Array[6];

extern int intRezepte[];
extern int ArrayCounter;
extern char IntString[];
extern bool remote_rezept;
uint8_t t;

void UART_init(void)
{
	PORTC.DIRCLR = PIN6_bm;	//UART IN
	PORTC.DIRSET = PIN7_bm; //UART OUT
	PORTC.PIN7CTRL = PORT_OPC_PULLUP_gc;

	USARTC1.BAUDCTRLB = 4 << 4;																								
	USARTC1.BAUDCTRLA = 12;	
	//USARTC1.BAUDCTRLB = 0b11010000;
	//USARTC1.BAUDCTRLA = 131; 																							
	USARTC1.CTRLB = USART_TXEN_bm | USART_RXEN_bm;																	
	USARTC1.CTRLC = USART_CHSIZE_8BIT_gc;																								
	USARTC1.CTRLA = USART_RXCINTLVL_HI_gc;
}

void Send_UART(char *data)
{
	uint8_t length = 0x00;
	uint8_t Counter = 0x00;
	
	length = strlen(data);
	
	while(Counter < length)
	{
		while (!(USARTC1.STATUS & USART_DREIF_bm));
		USARTC1.DATA = data[Counter];
		Counter++;
	}
	
	Counter = 0x00;
	while (!( USARTC1.STATUS & USART_DREIF_bm));
	//USARTC1.DATA = 0x0A;		//sendet /n
	while (!( USARTC1.STATUS & USART_DREIF_bm));
	//USARTC1.DATA = 0x0D;		//sendet /r
}

void release_uart_string(void)
{
	uart_str_complete = 0;
	uart_str_count = 0;
}

void release_global_uart_string(void)
{
	release_uart_string();
	global_uart_str_complete = 0;
}

int char2int(char zeigerAufChar)
{
	uint8_t Zahl = zeigerAufChar;
	switch(Zahl)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
	}
}

char* int2char(int Zahl)
{
	char *Zeiger;
	switch(Zahl)
	{
		case 0: *Zeiger = '0';
		break;
		case 1: *Zeiger = '1';
		break;
		case 2: *Zeiger = '2';
		break;
		case 3: *Zeiger = '3';
		break;
		case 4: *Zeiger = '4';
		break;
		case 5: *Zeiger = '5';
		break;
		case 6: *Zeiger = '6';
		break;
		case 7: *Zeiger = '7';
		break;
		case 8: *Zeiger = '8';
		break;
		case 9: *Zeiger = '9';
		break;
		default: *Zeiger = '\n';
	}
	return Zeiger;
}



int Array2Int (char Zahlenstring[], uint8_t lenght)
{
	int wert = 0;
	for(int i=0; i<lenght; i++)
	{
		wert = wert + (char2int(Zahlenstring[i])*pow(10, i));
	}
	return wert;
}

// Wird nach jedem empfangenen Zeichen aufgerufen
// Zeichen werden zu einem String zusammengefügt
ISR(USARTC1_RXC_vect)
{
	unsigned char nextChar;

	// Daten aus dem Puffer lesen
	nextChar = USARTC1.DATA;
	
	switch(nextChar)
	{
		case '+':
					count_plus++;
					break;
		case '#':
					count_hash++;
					break;
		default:
					if( nextChar != '\n' &&	nextChar != '\r' &&	uart_str_count < UART_MAXSTRLEN ) 
					{
						uart_string[uart_str_count] = nextChar;
						global_uart_string[uart_str_count] = nextChar;
						uart_str_count++;
					}
					else
					{
						Send_UART("Ende Zeichen oder Overflow erkannt");
						release_global_uart_string();	
					}
	}
	
	if (count_plus == 4 && count_hash == 4)
	{
		if ((global_uart_string[0] == 'g') && (global_uart_string[4] == 's')) //vermutlich ####get_status+++
		{
			Send_UART(Letzter_Status);
			release_global_uart_string();
		}
		if ((global_uart_string[0] == '0') && (global_uart_string[1] == ':')) //Rezept erkannt
		{
		//	Send_UART("Rezept erkannt");
			
			////////////////////////////////////////////
			
			for(int i=0; i<56; i++)
			{
				switch(global_uart_string[i])
				{
					case 35:   //Nichts unternehmen //#
					break;
					case 59:   ArrayCounter = char2int(global_uart_string[i-5]); //;
					for(int u=0; u<3; u++)
					{
						IntString[u] = global_uart_string[i-u-1];
					}
					t = char2int(global_uart_string[i-5])-1;
					intRezepte[t] = Array2Int(IntString, 3);
					Rezept_Array[t] = intRezepte[t];
					//cout << "IntRezepte[" << ArrayCounter-1 << "]: " << intRezepte[ArrayCounter-1]<< endl;
					break;
				}
			}
			
			///////////////////////////////////////////
			
			
			remote_rezept = true;
			release_global_uart_string();
		}
		count_plus = 0;
		count_hash = 0;		
	}
	

}


/* Backup ISR UART
ISR(USARTC1_RXC_vect)
{
	unsigned char nextChar;

	// Daten aus dem Puffer lesen
	nextChar = USARTC1.DATA;
	
	if( uart_str_complete == 0 ) {	// wenn uart_string gerade in Verwendung, neues Zeichen verwerfen
		
		// Daten werden erst in uart_string geschrieben, wenn nicht String-Ende/max Zeichenlänge erreicht ist/string gerade verarbeitet wird
		if( nextChar != '\n' &&
		nextChar != '\r' &&
		nextChar != '+' &&		// Bedeutet dass die Endsequenz erreicht wurde
		uart_str_count < UART_MAXSTRLEN ) {
			uart_string[uart_str_count] = nextChar;
			global_uart_string[uart_str_count] = nextChar;
			uart_str_count++;
		}
		else {
			uart_string[uart_str_count] = '\0';
			global_uart_string[uart_str_count] = '\0';
			uart_str_count = 0;
			uart_str_complete = 1;
			global_uart_str_complete = 1;
			//USARTC1.CTRLB &= ~(1<< USART_RXEN_bp);
		}
	}
	//if (global_uart_str_complete == 1)
	else
	{
		if ((global_uart_string[4] == 'g') && (global_uart_string[8] == 's')) //vermutlich ####get_status+++
		{
			Send_UART(Letzter_Status);
			release_global_uart_string();
		}
		if ((global_uart_string[4] == '0') && (global_uart_string[5] == ':')) //Rezept erkannt
		{
			Send_UART("Rezept erkannt");
			release_global_uart_string();
		}
	}
	


	//USARTC1.CTRLB = USART_RXEN_bm;
}

*/