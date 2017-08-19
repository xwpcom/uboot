cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_SYSTEM_NAME Linux)

enable_language( ASM-ATT)

#set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
#set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

SET(TARGET_APP uboot.elf)
project(${TARGET_APP})

AUX_SOURCE_DIRECTORY(./src SRC)

set(ASM_FILES 
src/head.s
)

set(SRC_LIST
	${SRC}
	)

SET(COMPILER_DIR /opt/hisi-linux/x86-arm/arm-hisiv300-linux)
SET(COMPILER_CROSS ${COMPILER_DIR}/bin/arm-hisiv300-linux-uclibcgnueabi-)
SET(CMAKE_C_COMPILER   ${COMPILER_CROSS}gcc)
SET(CMAKE_CXX_COMPILER ${COMPILER_CROSS}g++)
set(CMAKE_ASM-ATT_COMPILER ${COMPILER_CROSS}gcc)
SET(CMAKE_ASM-ATT_COMPILER_ARG1 "-c")

SET(CMAKE_CXX_FLAGS "-fno-exceptions -nostdlib -static -nostdinc++ -nostartfiles -nodefaultlibs -fno-builtin -fno-builtin-function -Wall -O2") 
link_libraries("-static -nostartfiles -nodefaultlibs -nostdlib -T../uboot.lds")

add_executable(${TARGET_APP} 
${ASM_FILES}   #注意head.o要放在最前面,s3c2440上电后是从地址0开始执行的
${SRC_LIST}
)

add_custom_command(
	OUTPUT uboot.bin 
	POST_BUILD
    COMMAND /opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/arm-hisiv300-linux-uclibcgnueabi-objcopy -O binary -S uboot.elf ../uboot.bin
	DEPENDS ${TARGET_APP}
	)
add_custom_target(uboot ALL DEPENDS uboot.bin)
