cmake_minimum_required(VERSION 3.16)



set(sources
    ${PROJ_DIR}/middleware/utility_print/printf/printf.c
)
set(includes
    ${PROJ_DIR}/middleware/utility_print/printf
)
set(priIncludes
)

add_library(UTILITY_PRINT STATIC ${sources})

target_include_directories(UTILITY_PRINT PUBLIC ${includes})


target_include_directories(UTILITY_PRINT PRIVATE ${priIncludes})
configcore(UTILITY_PRINT ${CMAKE_SOURCE_DIR})

target_compile_definitions(UTILITY_PRINT PUBLIC
    YTM32B1LE0
    CPU_YTM32B1LE0
)
target_compile_options(UTILITY_PRINT PUBLIC
    -fdiagnostics-color=always
)



target_link_libraries(UTILITY_PRINT
    GENERATED_CONFIG_TARGET
    GENERATED_SDK_TARGET
)
