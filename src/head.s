.extern     main
.text 
.global _start 
_start:
Reset:                  
    ldr sp, =4096           @ 设置栈指针，以下都是C函数，调用前需要设好栈
    bl  disable_watch_dog   // 关闭WATCHDOG，否则CPU会不断重启
    bl  clock_init          // 设置MPLL，改变FCLK、HCLK、PCLK
    bl  memsetup            // 设置存储控制器以使用SDRAM
    bl  copy_steppingstone_to_sdram     // 复制代码到SDRAM中
    ldr pc, =on_sdram                   // 跳到SDRAM中继续执行
on_sdram:
    ldr sp, =0x34000000     // 设置栈指针
    ldr lr, =halt_loop      // 设置返回地址
    ldr pc, =main           // 调用main函数
halt_loop:
    b   halt_loop
