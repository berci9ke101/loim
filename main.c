#include "functions.h"
#include "main_menu.h"
#include "difficulty.h"
#include "game.h"
#include "timer.h"
#include <time.h>
#include "debugmalloc.h"

int main()
{
    /*KEZDOERTEKEK BEALLITASA*/
    srand(time(0)); //kozonseg segitseg eloszlasahoz hasznalt randomszamgeneralas es a random kerdes kivalasztasahoz hasznalt random szam
    int difficulty = 0;
    int global_state = 0; //menuvaltozo inicializalasa

    /*konzolablak inicializalasa*/
    console_init();

    /*scoreboard rendezese*/
    read_sort_write();

    /*MAIN MENU, NEHEZSEG ES SCOREBOARD*/
    while (1)
    {
        if (global_state == 0) //ha a menuvaltozo 0 erteken van a fomenu ugrik elo
        {
            //MAIN MENU
            main_menu_init();
            main_menu_buttons(&global_state);
        }
        else if (global_state == 1) //ha a menuvaltozo 1 erteken van a nehezsegi szint valaszto ugrik elo
        {
            //DIFFICULTY
            difficulty_init();
            difficulty_buttons(&global_state, &difficulty);
        }
        else if (global_state == 2) //ha a menuvaltozo 2 erteken van a dicsosegtabla ugrik elo
        {
            //SCOREBOARD
            scoreboard_init();
            scoreboard_buttons(&global_state);
        }
        else if (global_state == 3) //ha a menuvaltozo 3 erteken van elkezdodiik a jatek
        {
            //GAME
            break;
        }
    }

    game(difficulty);

    return 0;
}
