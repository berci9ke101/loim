#include <stdio.h>
#include "functions.h"
#include "menu.h"

#ifdef _WIN32

#include <windows.h>

#endif

int main()
{
//UTF-8 kodolas beallitasa
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    //ablak nevenek es meretenek beallitasa
    init_console_window();

    init_main_menu();
    draw_rect_char(45, 5, 20, 10, "-|++++");


    int i;
    scanf("%d", &i);
    /*print_to_console("../UI/MAIN_MENU.txt");
    buttons();*/



    return 0;
}
