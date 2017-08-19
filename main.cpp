extern "C"
{
	#include "serial.h"
}
#include "s3c24xx.h"



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
	
    uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)

	puts("\r\nHello from s3c2440,use cmake hisi c++ compiler\r\n");
/*
    while(1)
    {
        // 从串口接收数据后，判断其是否数字或子母，若是则加1后输出
	    unsigned char c = getc();
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

