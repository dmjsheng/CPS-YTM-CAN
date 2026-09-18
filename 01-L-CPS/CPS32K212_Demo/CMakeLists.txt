set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

SET(CMAKE_C_COMPILER_WORKS TRUE)
SET(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_C_STANDARD 99)

project(CPS32K212_Demo C)

include_directories(
        App
        Device/CPS32K214LSLFMT
        Driver/Include
        Device/CMSIS

        RTOS/QuarkTS-7.3.3/include
)

file(GLOB SOURCES
        App/*.c
        Device/CPS32K214LSLFMT/*.c
        Driver/Source/*.c

        RTOS/QuarkTS-7.3.3/*.c
)

#-fno-elide-constructors 通过参数-fno-elide-constructors关闭g++的编译优�?#__attribute__((optimize（�O0”）)) 让GCC 不�优化程�
add_compile_options(-Os)#-Os -Ofast -Og
add_compile_options(-mthumb -march=armv6s-m -mcpu=cortex-m0plus)#-mthumb-interwork
add_compile_options(-fdata-sections -ffunction-sections -Wextra -Wfatal-errors)
add_compile_options(-Wall -Wtype-limits -Wshadow -Wundef)
# add_compile_options(-fabi-version=0 -fno-move-loop-invariants)
add_compile_options(-ffreestanding)
add_compile_options(-fmessage-length=0 -fsigned-char -g3)

enable_language(ASM)
list(INSERT SOURCES 0 App/main.c)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Device/CPS32K214LSLFMT/GCC_cps32k11x.ld)

add_link_options(-T ${LINKER_SCRIPT})
add_link_options(-nostartfiles)
add_link_options(--entry=Reset_Handler -ggdb3 -n)
add_link_options(-mthumb -march=armv6-m -mcpu=cortex-m0plus)#-mthumb-interwork
add_link_options(-specs=nano.specs -specs=nosys.specs)
add_link_options(-Wl,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--gc-sections)

enable_language(ASM)
SET(STARTUP_SRC ${CMAKE_SOURCE_DIR}/Device/CPS32K214LSLFMT/startup_cps32k21x_.S)
set_source_files_properties(${STARTUP_SRC} PROPERTIES COMPILE_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp -g3")

add_executable(${PROJECT_NAME}.elf ${STARTUP_SRC} ${SOURCES} ${RTOS_SOURCES})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(ASM_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.S)

add_custom_target(generate_hex ALL
    COMMAND arm-none-eabi-objcopy -Oihex CPS32K212_Demo.elf CPS32K212_Demo.hex
    COMMAND arm-none-eabi-objcopy -Obinary CPS32K212_Demo.elf CPS32K212_Demo.bin
    DEPENDS CPS32K212_Demo.elf
)
