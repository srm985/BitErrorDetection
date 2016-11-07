//#include <asf.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "UART.h"

void UART_init(int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)(baud);
	
	UCSR0B = (1 << RXEN0);
	//UCSR0C = (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00);    
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_PutChar(unsigned char c)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

unsigned char UART_ReadChar(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

