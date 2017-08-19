.extern     main
.text 
.global _start 
_start:
Reset:                  
    ldr sp, =4096           @ ����ջָ�룬���¶���C����������ǰ��Ҫ���ջ
    bl  disable_watch_dog   // �ر�WATCHDOG������CPU�᲻������
    bl  clock_init          // ����MPLL���ı�FCLK��HCLK��PCLK
    bl  memsetup            // ���ô洢��������ʹ��SDRAM
    bl  copy_steppingstone_to_sdram     // ���ƴ��뵽SDRAM��
    ldr pc, =on_sdram                   // ����SDRAM�м���ִ��
on_sdram:
    ldr sp, =0x34000000     // ����ջָ��
    ldr lr, =halt_loop      // ���÷��ص�ַ
    ldr pc, =main           // ����main����
halt_loop:
    b   halt_loop