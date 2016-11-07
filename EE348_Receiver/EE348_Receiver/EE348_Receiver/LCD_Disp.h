#ifndef LCD_Disp_h_
#define LCD_Disp_h_

#define LCD_Address			0x4E	//I2C address location

#define En					0x04
#define Backlight			0x08
#define RS					0x01					


//******LCD Shift*****
#define Right_Cur			0x04
#define Left_Cur			0x00
#define Disp_Shift			0x08
#define Cur_Shift			0x00


void LCD_init(void);
void LCD_Write(unsigned char data, uint8_t RS_En);
void togle_EN(uint8_t data, uint8_t RS_En);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Shift(uint8_t shift, uint8_t direction, uint8_t quantity);
void LCD_On(uint8_t valid);


#endif