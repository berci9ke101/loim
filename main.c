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
    init_console_window();

    debug_console(119, 25);

    init_main_menu();
    //draw_rect_char(0, 0, 120, 25, "═║╔╗╚╝");

    /*print_to_console("../UI/MAIN_MENU.txt");
    buttons();*/


    while (true)
    {
        int key = econio_getch();

        if (key == KEY_UP)
            init_main_menu();
        else if (key == KEY_DOWN)
            init_main_menu2();
        else if (key == KEY_ESCAPE)
            break;
    }


    return 0;
}
