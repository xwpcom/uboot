extern "C"
{
	#include "s3c24xx.h"
	#include "serial.h"
}

/*
 * ��ʼ��UART0
 * 115200,8N1,������
 */
void uart0_init(void)
{
    GPHCON  |= 0xa0;    // GPH2,GPH3����TXD0,RXD0
    GPHUP   = 0x0c;     // GPH2,GPH3�ڲ�����

    ULCON0  = 0x03;     // 8N1(8������λ���޽��飬1��ֹͣλ)
    UCON0   = 0x05;     // ��ѯ��ʽ��UARTʱ��ԴΪPCLK
    UFCON0  = 0x00;     // ��ʹ��FIFO
    UMCON0  = 0x00;     // ��ʹ������
    UBRDIV0 = UART_BRD; // ������Ϊ115200
}

/*
 * ����һ���ַ�
 */
void putc(unsigned char c)
{
    /* �ȴ���ֱ�����ͻ������е������Ѿ�ȫ�����ͳ�ȥ */
    while (!(UTRSTAT0 & TXD0READY));
    
    /* ��UTXH0�Ĵ�����д�����ݣ�UART���Զ��������ͳ�ȥ */
    UTXH0 = c;
}

void puts(const char *str)
{
	if(!str)
	{
		return;
	}

	while(1)
	{
		unsigned char ch=*str++;
		if(ch==0)
		{
			break;
		}
		putc(ch);
	}
}

/*
 * �����ַ�
 */
unsigned char getc(void)
{
    /* �ȴ���ֱ�����ջ������е������� */
    while (!(UTRSTAT0 & RXD0READY));
    
    /* ֱ�Ӷ�ȡURXH0�Ĵ��������ɻ�ý��յ������� */
    return URXH0;
}

/*
 * �ж�һ���ַ��Ƿ�����
 */
int isDigit(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;       
}

/*
 * �ж�һ���ַ��Ƿ�Ӣ����ĸ
 */
int isLetter(unsigned char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    else if (c >= 'A' && c <= 'Z')
        return 1;       
    else
        return 0;
}
