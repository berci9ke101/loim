#include "functions.h"
#include "main_menu.h"
#include "scoreboard.h"
#include <stdio.h>
#include "econio.h"

int main()
{
    int global_state = 0;
    console_init();

    while (1)
    {
        if (global_state == 0)
        {
            //MAIN MENU
            main_menu_init();
            main_menu_buttons(/*global_state*/);
        }
        else if (global_state == 1)
        {
            //SCOREBOARD
            scoreboard_init();
            scoreboard_buttons();
        }
        else if (global_state == 2)
        {
            break;
        }
    }

    econio_clrscr();
    econio_gotoxy(0, 0);
    printf("jatek");
    return 0;
}

