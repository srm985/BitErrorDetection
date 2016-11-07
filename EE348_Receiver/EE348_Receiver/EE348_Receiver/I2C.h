#ifndef I2C_H
#define I2C_H   

#include <avr/io.h>

//#define I2C_READ    1
//#define I2C_Write   0


extern void I2C_init(void);
extern void I2C_Stop(void);
extern unsigned char I2C_Start(unsigned char addr);
extern unsigned char I2C_Rep_Start(unsigned char addr);
extern unsigned char I2C_Start_Wait(unsigned char addr);

 
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
extern unsigned char I2C_Write(unsigned char data);


/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
extern unsigned char I2C_ReadAck(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char I2C_ReadNak(void);

/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either I2C_ReadAck or I2C_ReadNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char I2C_read(unsigned char ack);
#define I2C_read(ack)  (ack) ? I2C_ReadAck() : I2C_ReadNak(); 


/**@}*/
#endif
