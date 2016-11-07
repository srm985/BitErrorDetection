/***************************************
       Control of 20x4 I2C LCD
****************************************/

//#include <asf.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "LCD_Disp.h"
#include "I2C.h"


void LCD_init()
{
	I2C_init();	//Initialize I2C protocol
	
	//*****Init Three Times*****
	LCD_Write(0x03, 0);
	_delay_ms(5);
	LCD_Write(0x03, 0);
	_delay_us(150);
	LCD_Write(0x03, 0);
	_delay_us(150);
	
	LCD_Write(0x02, 0);
	
	LCD_Write(0b00101000, 0);

	LCD_Write(0b00001000, 0);
	
	LCD_Write(0b00000001, 0);
	
	LCD_Write(0b00001100, 0);	//Set cursor options
}

void LCD_Write(unsigned char data, uint8_t RS_En)
{
	I2C_Start(LCD_Address);
	
	//*****Write Upper Four Bits*****
	I2C_Write((data & 0xF0) | Backlight | RS_En);
	togle_EN(data & 0xF0, RS_En);
	
	//*****Write Lower Four Bits*****
	I2C_Write(((data << 4) & 0xF0) | Backlight | RS_En);
	togle_EN((data << 4) & 0xF0, RS_En);
	
	I2C_Stop();
}

void togle_EN(uint8_t data, uint8_t RS_En)
{
	I2C_Write(data | Backlight | En | RS_En);
	_delay_us(1);
	I2C_Write((data | Backlight | RS_En) & ~En);
	_delay_us(50);
}

void LCD_Clear()
{
	LCD_Write(0x01, 0);
}

void LCD_Home()
{
	LCD_Write(0x02, 0);
	_delay_ms(2);
}

void LCD_Shift(uint8_t shift, uint8_t direction, uint8_t quantity)
{
	while(quantity)
	{
		LCD_Write(0x10 | shift | direction, 0);
		_delay_us(50);	//required 37usec pause
		quantity--;
	}
}

void LCD_On(uint8_t valid)
{
	LCD_Write(((valid << 2) | 0x08) & 0x0C, 0);
	_delay_us(50);	//required 37usec pause
}