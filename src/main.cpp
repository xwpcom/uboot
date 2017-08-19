extern "C"
{
	#include "serial.h"
}
#include "s3c24xx.h"
#include "base.h"


#define	GPFCON		(*(volatile unsigned long *)0x56000050)
#define	GPFDAT		(*(volatile unsigned long *)0x56000054)

#define	GPF4_out	(1<<(4*2))
#define	GPF5_out	(1<<(5*2))
#define	GPF6_out	(1<<(6*2))

void  wait(volatile unsigned long dly)
{
	for(; dly > 0; dly--);
}

//todo:需要一个内存管理器
//最简单的实现方法:选一块内存，只负责new,而delete什么都不做
//仅供测试使用,2440开发板内存64MB,足够大了
void *operator new(unsigned int bytes)
{
	puts("call new\r\n");

	static unsigned char *p= (unsigned char*)(0x30000000 + 1024 * 256);
	unsigned char *addr = p;
	p += bytes;

	//align with 4
	if ((bytes % 4))
	{
		p += (4-(bytes % 4));
	}
	
	return addr;
}

void operator delete(void *p)
{
	//do nothing
	puts("call delete\r\n");
}


class Main
{
public:
	static int main();
};

int Main::main()
{
	uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)

	puts("\r\nHello from uboot,vs2015#1\r\n");
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
		Base *b = new Base();
		delete b;
	}

	unsigned long i = 0;

	GPFCON = GPF4_out | GPF5_out | GPF6_out;		// 将LED1,2,4对应的GPF4/5/6三个引脚设为输出

	while (1) {
		wait(30000);
		GPFDAT = (~(i << 4));	 	// 根据i的值，点亮LED1,2,4
		if (++i == 8)
			i = 0;
	}

	return 0;
}

extern "C" int main()
{
	return Main::main();
}

