cmake_minimum_required(VERSION 3.16)



set(sources
    ${PROJ_DIR}/board/clock_config.c
    ${PROJ_DIR}/board/pin_mux.c
    ${PROJ_DIR}/board/RamInit0.S
    ${PROJ_DIR}/board/RamInit1.c
    ${PROJ_DIR}/board/RamInit2.c
    ${PROJ_DIR}/board/startup.S
    ${PROJ_DIR}/board/vector.S
    ${PROJ_DIR}/board/vector_table_copy.c
    ${PROJ_DIR}/board/interrupt_config.c
    ${PROJ_DIR}/board/dma_config.c
    ${PROJ_DIR}/board/can_config.c
    ${PROJ_DIR}/board/i2c_config.c
    ${PROJ_DIR}/board/uart_config.c
    ${PROJ_DIR}/board/utility_print_config.c
)
set(includes
    ${PROJ_DIR}/board
)
set(priIncludes
)

add_library(GENERATED_CONFIG_TARGET STATIC ${sources})

target_include_directories(GENERATED_CONFIG_TARGET PUBLIC ${includes})


target_include_directories(GENERATED_CONFIG_TARGET PRIVATE ${priIncludes})
configcore(GENERATED_CONFIG_TARGET ${CMAKE_SOURCE_DIR})

target_compile_definitions(GENERATED_CONFIG_TARGET PUBLIC
    YTM32B1LE0
    CPU_YTM32B1LE0
)
target_compile_options(GENERATED_CONFIG_TARGET PUBLIC
    -fdiagnostics-color=always
)



target_link_libraries(GENERATED_CONFIG_TARGET
    GENERATED_SDK_TARGET
    UTILITY_PRINT
)
