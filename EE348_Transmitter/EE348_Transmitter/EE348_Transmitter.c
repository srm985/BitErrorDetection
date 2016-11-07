/*
 * EE348_Transmitter.c
 *
 * Created: 24.04.14 17:47:41
 *  Author: Sean McQuay
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"

#define Tx1		0x81
#define Tx2		0x7E

void TxChar_Raw(unsigned char address, unsigned char data);
void TxChar_Encoded(unsigned char address, unsigned char data);

int main(void)
{
	DDRD |= 0b00100110;
	PORTD |= 0b00100101;
	
	//UART_init(51);		//1200bps
	UART_init(155);			//400bps
	//UART_init(311);		//200bps
	
	while(1)
	{	
		while(PIND & 0x10)	//Encoded data jumper setting
		{
			for(int i = 0; i <= 9; i++)
			{
				TxChar_Encoded(Tx1, i + '0');
				_delay_ms(500);
			}
		}
		while(PIND & 0x08)	//Raw data jumper setting
		{
			for(int i = 0; i <= 9; i++)
			{
				TxChar_Raw(Tx1, i + '0');
				_delay_ms(500);
			}
		}
	}
}


void TxChar_Raw(unsigned char address, unsigned char data)
{	
	UART_PutChar(0xAA);
	UART_PutChar(0xAA);
	UART_PutChar(address);
	UART_PutChar(address);
	UART_PutChar(data);
	return;
}


void TxChar_Encoded(unsigned char address, unsigned char data)
{
	unsigned char dataCodes[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char tmp = 0;
	
	for(int i = 0; i <= 7; i++)
	{
		tmp = ((address >> i) & 0x01);
		
		if(tmp == 0x00)
		{
			dataCodes[i] = 0x00;
		}
		else if(tmp == 0x01)
		{
			dataCodes[i] = 0xFF;
		}
	}
	
	for(int i = 0; i <= 7; i++)
	{
		tmp = ((data >> i) & 0x01);
		
		if(tmp == 0x00)
		{
			dataCodes[i+8] = 0x00;
		}
		else if(tmp == 0x01)
		{
			dataCodes[i+8] = 0xFF;
		}
	}
	UART_PutChar(0xAA);
	UART_PutChar(0xAA);
	UART_PutChar(address);
	UART_PutChar(dataCodes[0]);
	UART_PutChar(dataCodes[1]);
	UART_PutChar(dataCodes[2]);
	UART_PutChar(dataCodes[3]);
	UART_PutChar(dataCodes[4]);
	UART_PutChar(dataCodes[5]);
	UART_PutChar(dataCodes[6]);
	UART_PutChar(dataCodes[7]);
	UART_PutChar(dataCodes[8]);
	UART_PutChar(dataCodes[9]);
	UART_PutChar(dataCodes[10]);
	UART_PutChar(dataCodes[11]);
	UART_PutChar(dataCodes[12]);
	UART_PutChar(dataCodes[13]);
	UART_PutChar(dataCodes[14]);
	UART_PutChar(dataCodes[15]);
}



/*void TxChar_Encoded(unsigned char address, unsigned char data)
{
	unsigned char dataCodes[16] = {0,0,0,0,0,0,0,0};
	unsigned char tmp = 0;
	
	for(int i = 0; i <= 3; i++)
	{
		tmp = ((address >> (i*2)) & 0x03);
		
		if(tmp == 0x00)
		{
			dataCodes[i] = 0x01;
		}
		else if(tmp == 0x01)
		{
			dataCodes[i] = 0x62;
		}
		else if(tmp == 0x02)
		{
			dataCodes[i] = 0x94;
		}
		else if(tmp == 0x03)
		{
			dataCodes[i] = 0xC8;
		}
	}
	
	for(int i = 0; i <= 3; i++)
	{
		tmp = ((data >> (i*2)) & 0x03);
		
		if(tmp == 0x00)
		{
			dataCodes[i+4] = 0x01;
		}
		else if(tmp == 0x01)
		{
			dataCodes[i+4] = 0x62;
		}
		else if(tmp == 0x02)
		{
			dataCodes[i+4] = 0x94;
		}
		else if(tmp == 0x03)
		{
			dataCodes[i+4] = 0xC8;
		}
	}
	UART_PutChar(0x00);
	UART_PutChar(0x00);
	UART_PutChar(address);
	UART_PutChar(dataCodes[0]);
	UART_PutChar(dataCodes[1]);
	UART_PutChar(dataCodes[2]);
	UART_PutChar(dataCodes[3]);
	UART_PutChar(dataCodes[4]);
	UART_PutChar(dataCodes[5]);
	UART_PutChar(dataCodes[6]);
	UART_PutChar(dataCodes[7]);
}*/