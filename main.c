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

    //debug_console(119, 25);

    init_main_menu();
    //draw_rect_char(0, 0, 120, 25, "═║╔╗╚╝");

    /*print_to_console("../UI/MAIN_MENU.txt");
    buttons();*/

    int menu_state = 0;
    char a, b, c;

    while (true)
    {
        int key = econio_getch();
        econio_flush();

        if (key == KEY_UP)
        {
            if (menu_state >= -2 && menu_state < 0)
            {
                menu_state++;
            }
        }
        else if (key == KEY_DOWN)
        {
            if (menu_state > -2 && menu_state <= 0)
            {
                menu_state--;
            }
        }
        else if (key == KEY_ENTER)
        {
            if (menu_state == -2)
            {
                break;
            }
        }

        main_menu_state_switcher(menu_state, &a, &b, &c);
        main_menu_select(a, b, c);

    }

    return 0;
}

