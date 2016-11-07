#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "UART.h"

void UART_init(int baud)
{
	UBRRH = (unsigned char)(baud >> 8);
	UBRRL = (unsigned char)(baud);
	
	UCSRB = (1 << TXEN);
	//UCSRC = (1 << UPM1) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void UART_PutChar(unsigned char c)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = c; 
}

unsigned char UART_ReadChar(void)
{
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}