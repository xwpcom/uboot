#pragma once

void uart0_init(void);
void putc(unsigned char c);
void puts(const char *str);
unsigned char getc(void);
int isDigit(unsigned char c);
int isLetter(unsigned char c);

#define TXD0READY   (1<<2)
#define RXD0READY   (1)

#define PCLK            50000000    // init.c中的clock_init函数设置PCLK为50MHz
#define UART_CLK        PCLK        //  UART0的时钟源设为PCLK
#define UART_BAUD_RATE  115200      // 波特率
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

