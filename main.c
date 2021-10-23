#include <stdio.h>
#include "functions.h"
#include "menu.h"
#include "econio.h"

#ifdef _WIN32

#include <windows.h>

#endif

int main()
{
    //ablak nevenek, kodolasanak es meretenek beallitasa
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    init_console_window();

    init_main_menu();
    //draw_rect_char(0, 0, 120, 25, "═║╔╗╚╝");

    int i;
    scanf("%d", &i);
    /*print_to_console("../UI/MAIN_MENU.txt");
    buttons();*/



    return 0;
}
