cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_SYSTEM_NAME Linux)

enable_language( ASM )

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

SET(TARGET_APP uboot++)
project(${TARGET_APP})

AUX_SOURCE_DIRECTORY(. SRC)
#${SRC} += crt0.S

set(ASM_FILES 
crt0.S
head.S	
)

set(SRC_LIST
	${SRC}
	)
add_executable(${TARGET_APP} 
#${ASM_FILES}
${SRC_LIST}
)

SET(COMPILER_DIR /opt/hisi-linux/x86-arm/arm-hisiv300-linux)
SET(COMPILER_CROSS ${COMPILER_DIR}/bin/arm-hisiv300-linux-uclibcgnueabi-)
SET(CMAKE_C_COMPILER   ${COMPILER_CROSS}gcc)
SET(CMAKE_CXX_COMPILER ${COMPILER_CROSS}g++)

SET(CMAKE_CXX_FLAGS "-fno-exceptions -nostdlib -static -nostdinc++ -nostartfiles -nodefaultlibs -fno-builtin -fno-builtin-function -Wall -O2") 