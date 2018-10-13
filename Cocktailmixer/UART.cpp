
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
}

void release_global_uart_string(void)
{
	release_uart_string();
	global_uart_str_complete = 0;
}


// Wird nach jedem empfangenen Zeichen aufgerufen
// Zeichen werden zu einem String zusammengefügt
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
	if (global_uart_str_complete == 1)
	{
		if ((global_uart_string[4] == 'g') && (global_uart_string[8] == 's')) //vermutlich ####get_status+++
		{
			Send_UART(Letzter_Status);
			release_global_uart_string();
		}
	}
	
		//USARTC1.CTRLB = USART_RXEN_bm;
}


