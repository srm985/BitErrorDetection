#ifndef UART_h_
#define UART_h_

void UART_init(int baud);
void UART_PutChar(unsigned char c);
unsigned char UART_ReadChar(void);

#endif