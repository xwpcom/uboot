objs :=  head.o init.o serial.o main.o

uboot++.bin: $(objs)
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-ld -static -nostartfiles -nodefaultlibs -nostdlib -Tleds.lds -o uboot++.elf $^
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-objcopy -O binary -S uboot++.elf $@
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-objdump -D -m arm uboot++.elf > uboot++.dis
	
%.o:%.c
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-gcc -nostdinc++ -nostartfiles -nodefaultlibs -nostdlib -fno-builtin -fno-builtin-function -Wall -O2 -c -o $@ $<

%.o:%.cpp
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-gcc -Wno-frame-address -nostdlib -fno-omit-frame-pointer  -static -nostdinc++ -nostartfiles -nodefaultlibs -nostdlib -fno-builtin -fno-builtin-function -Wall -O2 -c -o $@ $<

%.o:%.S
	/opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f uboot++.bin uboot++.elf uboot++.dis *.o		
	