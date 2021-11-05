#include "functions.h"
#include "main_menu.h"
#include "scoreboard.h"
#include "game.h"
#include "timer.h"
#include <time.h>


#include "windows.h"
#include "econio.h"
#include <stdio.h>

int main()
{
    int minute = 0;
    int second = 0;

    int global_state = 0; //menuvaltozo inicializalasa
    console_init(); //konzolablak inicializalasa

    while (1)
    {
        if (global_state == 0) //ha a menuvaltozo 0 erteken van a fomenu ugrik elo
        {
            //MAIN MENU
            main_menu_init();
            main_menu_buttons(&global_state);
        }
        else if (global_state == 1) //ha a menuvaltozo 1 erteken van a dicsosegtabla ugrik elo
        {
            //SCOREBOARD
            scoreboard_init();
            scoreboard_buttons(&global_state);
        }
        else if (global_state == 2) //ha a menuvaltozo 2 erteken van elkezdodiik a jatek
        {
            //GAME
            game_init();
            //game_buttons(&global_state);
            break;
        }
    }

    time_t prev_time = time(0);

    while (1)
    {
        print_time(minute, second);
        prev_time = timer(prev_time, &minute, &second);

        //pressF();

        //int key = econio_getch(); //lenyomott gomb bekerese
        int key = GetAsyncKeyState(VK_RETURN);

        econio_flush(); //folyekonyabb kirajzolas

        econio_gotoxy(12, 12);
        printf("%d", key);

        if ((key & 0x01))
        {
            econio_gotoxy(0, 0);
            printf("%02d:%02d", minute, second);
            econio_sleep(1);
            system("NAGYHF.exe");
            exit(0);
        }

    }


    return 0;
}

