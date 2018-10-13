/*
 * UART.h
 *
 * Created: 23.01.2018 16:26:21
 *  Author: Basti
 */ 


#ifndef UART_H_
#define UART_H_

void Send_UART(char *data);

void UART_init(void);

void Int_init(void);

void release_uart_string(void);
void release_global_uart_string(void);


#endif /* UART_H_ */