/*
 * EE348_Receiver.c
 *
 * Created: 24.04.14 16:05:57
 *  Author: Sean McQuay
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "I2C.h"
#include "LCD_Disp.h"

#define	Tx1		0x81
#define Tx2		0x7E

int main(void)
{
	DDRB |= 0b00001001;
	PORTB |= 0b00001001;
	
	unsigned char dataCodes[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char address = 0;
	unsigned char data = 0;
	unsigned char tmp = 0;
	unsigned char count_zero, count_one = 0;
	
	LCD_init();
	//UART_init(51);		//1200bps
	UART_init(155);			//400bps
	//UART_init(311);		//200bps
	
	LCD_Write('T', RS);
	LCD_Write('r', RS);
	LCD_Write('a', RS);
	LCD_Write('n', RS);
	LCD_Write('s', RS);
	LCD_Write('m', RS);
	LCD_Write('i', RS);
	LCD_Write('t', RS);
	LCD_Write('t', RS);
	LCD_Write('e', RS);
	LCD_Write('r', RS);
	LCD_Write(':', RS);
	LCD_Shift(Cur_Shift, Right_Cur, 8);
	
	LCD_Write('D', RS);
	LCD_Write('a', RS);
	LCD_Write('t', RS);
	LCD_Write('a', RS);
	LCD_Write(':', RS);
	LCD_Shift(Cur_Shift, Right_Cur, 2);
		
	while(1)
	{
		while(PINB & 0x04)	//Encoded data jumper setting
		{
			while(UART_ReadChar() != Tx1)	//Wait for Tx synchronization
			{
			}
			
			dataCodes[0] = UART_ReadChar();
			dataCodes[1] = UART_ReadChar();
			dataCodes[2] = UART_ReadChar();
			dataCodes[3] = UART_ReadChar();
			dataCodes[4] = UART_ReadChar();
			dataCodes[5] = UART_ReadChar();
			dataCodes[6] = UART_ReadChar();
			dataCodes[7] = UART_ReadChar();
			dataCodes[8] = UART_ReadChar();
			dataCodes[9] = UART_ReadChar();
			dataCodes[10] = UART_ReadChar();
			dataCodes[11] = UART_ReadChar();
			dataCodes[12] = UART_ReadChar();
			dataCodes[13] = UART_ReadChar();
			dataCodes[14] = UART_ReadChar();
			dataCodes[15] = UART_ReadChar();
			
			
			for(int i = 0; i <= 7; i++)
			{
				count_zero = count_one = 0;
				
				for(int j = 0; j <= 7; j++)
				{
					if((((dataCodes[i] ^ 0x00) >> j) & 0x01) == 1)
					{
						count_zero  ++;
					}
					if((((dataCodes[i] ^ 0xFF) >> j) & 0x01) == 1)
					{
						count_one++;
					}
				}
				if(count_zero < count_one)
				{
					address |= (0x00 << i);
				}
				else if(count_one < count_zero)
				{
					address |= (0x01 << i);
				}
			}
			
			
			for(int i = 0; i <= 7; i++)
			{
				count_zero = count_one = 0;
				
				for(int j = 0; j <= 7; j++)
				{
					if((((dataCodes[i+8] ^ 0x00) >> j) & 0x01) == 1)
					{
						count_zero++;
					}
					if((((dataCodes[i+8] ^ 0xFF) >> j) & 0x01) == 1)
					{
						count_one++;
					}
				}
				if(count_zero < count_one)
				{
					data |= (0x00 << i);
				}
				else if(count_one < count_zero)
				{
					data |= (0x01 << i);
				}
			}
			
			if(address == Tx1 && data >= '0' && data <= '9')
			{
				LCD_Write(data, RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('0', RS);
				LCD_Write('x', RS);
				LCD_Write('8', RS);
				LCD_Write('1', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
				
			}
			else if(address == Tx2 && data >= '0' && data <= '9')
			{
				LCD_Write(data, RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('0', RS);
				LCD_Write('x', RS);
				LCD_Write('7', RS);
				LCD_Write('E', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
			}
			else
			{
				LCD_Write('!', RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('!', RS);
				LCD_Write(' ', RS);
				LCD_Write(' ', RS);
				LCD_Write(' ', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
			}
			
			
			address = data = 0;
		}
		
		
		while(PINB & 0x02)	//Raw data jumper setting
		{
			address = data = 0;
			
			while(UART_ReadChar() != Tx1) //Wait for Tx synchronization 
			{
			}
			
			address = UART_ReadChar();
			data = UART_ReadChar();
			
			if(address == Tx1 && data >= '0' && data <= '9')
			{
				LCD_Write(data, RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('0', RS);
				LCD_Write('x', RS);
				LCD_Write('8', RS);
				LCD_Write('1', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
				
			}
			else if(address == Tx2 && data >= '0' && data <= '9')
			{
				LCD_Write(data, RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('0', RS);
				LCD_Write('x', RS);
				LCD_Write('7', RS);
				LCD_Write('E', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
			}
			else
			{
				LCD_Write('!', RS);
				LCD_Shift(Cur_Shift, Left_Cur, 14);
				LCD_Write('!', RS);
				LCD_Write(' ', RS);
				LCD_Write(' ', RS);
				LCD_Write(' ', RS);
				LCD_Shift(Cur_Shift, Right_Cur, 9);
			}
		}
	}
}