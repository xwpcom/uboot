extern "C"
{
	//#include "serial.h"
}
#include "s3c24xx.h"

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

/*
 * 初始化UART0
 * 115200,8N1,无流控
 */
void uart0_init(void)
{
    GPHCON  |= 0xa0;    // GPH2,GPH3用作TXD0,RXD0
    GPHUP   = 0x0c;     // GPH2,GPH3内部上拉

    ULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
    UCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
    UFCON0  = 0x00;     // 不使用FIFO
    UMCON0  = 0x00;     // 不使用流控
    UBRDIV0 = UART_BRD; // 波特率为115200
}

/*
 * 发送一个字符
 */
void putc(unsigned char c)
{
    /* 等待，直到发送缓冲区中的数据已经全部发送出去 */
    while (!(UTRSTAT0 & TXD0READY));
    
    /* 向UTXH0寄存器中写入数据，UART即自动将它发送出去 */
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
 * 接收字符
 */
unsigned char getc(void)
{
    /* 等待，直到接收缓冲区中的有数据 */
    while (!(UTRSTAT0 & RXD0READY));
    
    /* 直接读取URXH0寄存器，即可获得接收到的数据 */
    return URXH0;
}

/*
 * 判断一个字符是否数字
 */
int isDigit(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;       
}

/*
 * 判断一个字符是否英文字母
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

#define	GPFCON		(*(volatile unsigned long *)0x56000050)
#define	GPFDAT		(*(volatile unsigned long *)0x56000054)

#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))

void  wait(volatile unsigned long dly)
{
	for(; dly > 0; dly--);
}

class Base
{
public:
	Base()
	{
		puts("Base::Base()\r\n");
	}	
	~Base()
	{
		puts("Base::~Base()\r\n");
	}	
};

extern "C" int main()
{
	
    unsigned char c=0;
    uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)

	puts("\r\nhello from s3c2440,use hisi c++ compiler\r\n");
/*
    while(1)
    {
        // 从串口接收数据后，判断其是否数字或子母，若是则加1后输出
        c = getc();
        //if (isDigit(c) || isLetter(c))
        if(c==0x0D)
        {
        	puts("\r\n");
        }
        else
    	{
	        putc(c);
    	}
    }
    //*/

	{
		Base b;
	}
	
	unsigned long i = 0;

	GPFCON = GPF4_out|GPF5_out|GPF6_out;		// 将LED1,2,4对应的GPF4/5/6三个引脚设为输出

	while(1){
		wait(30000);
		GPFDAT = (~(i<<4));	 	// 根据i的值，点亮LED1,2,4
		if(++i == 8)
			i = 0;
	}



	return 0;
}

