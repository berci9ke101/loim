cmake_minimum_required(VERSION 3.20)
project(NAGYHF C)

set(CMAKE_C_STANDARD 99)

add_executable(NAGYHF main.c functions.c functions.h econio.c econio.h main_menu.c main_menu.h draw.c draw.h game.c game.h scoreboard.c scoreboard.h timer.c timer.h difficulty.c difficulty.h question.c question.h debugmalloc.h)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(NAGYHF PRIVATE DEBUG=1)
endif ()
