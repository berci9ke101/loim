cmake_minimum_required(VERSION 3.20)
project(NAGYHF C)

set(CMAKE_C_STANDARD 99)

add_executable(NAGYHF main.c functions.c functions.h econio.c econio.h menu.c menu.h draw.c draw.h)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(NAGYHF PRIVATE DEBUG=1)
endif ()
