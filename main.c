#include "functions.h"
#include "main_menu.h"
#include "scoreboard.h"
#include "difficulty.h"
#include "game.h"
#include "draw.h"
#include "timer.h"
#include <time.h>


#include "windows.h"
#include "econio.h"
#include <stdio.h>

int main()
{
    /*KEZDOERTEKEK BELLITASA*/
    srand(time(0)); //kozonseg segitseg eloszlasahoz hasznalt randomszamgeneralas
    int difficulty = 0;
    int global_state = 0; //menuvaltozo inicializalasa

    /*konzolablak inicializalasa*/
    console_init();

    /*MAIN MENU ES SCOREBOARD*/
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

    /*GAME*/

    /*ORA INICIALIZALASA*/
    int hour = 0;
    int minute = 0;
    int second = 0;
    time_t prev_time = time(0);

    /*KERDES VALTOZO, SEGITSEGEK ES A NYERT OSSZEG "NULLAZASA"*/
    int questionnum = 1;
    int amount = 0;
    int fix_amount = 0;

    /*MAGA A JATEK*/
    game_init(); //felhasznaloi felulet kirajzolasa es a jatek inicializalasa
    draw_audience("A");

    while (1)
    {
        econio_flush(); //folyekonyabb kirajzolas
        /*TIMER*/
        print_time(hour, minute, second); //ido kiiratasa
        prev_time = timer(prev_time, &hour, &minute, &second); //maga a timer fuggvenye
        pressF(); //f billentyu folyamatos nyomkodasa
        //ez azert kell, mert a conioban a getch egyidejuleg erzekeli a billentyülenyomasokat es addig var a program,
        //amig nem kap lenyomott billentyut. Ezert imitalunk egy billentyulenyomast, hogy a timer kiirasa folyekony legyen.

        /*oldalso nyeremeny tablazat frissitese*/
        econio_sleep(0.001); //hogy ne villodzon a kirajzolt nyilacska
        arrow_and_reward(questionnum, &amount, &fix_amount); //nyilacska kirajzolasa a jelnlegi kerdes alapjan

        /*kerdesek es valaszok betoltese*/


        /*vezerles*/

        int key = econio_getch(); //lenyomott gomb bekerese
        if (key == KEY_ESCAPE)
        {
            econio_gotoxy(0, 0);
            printf("%02d:%02d:%02d", hour, minute, second);
            econio_sleep(1);
            system("NAGYHF.exe");
            return 0;
        }

        /*kilepeskor a nev megadasa*/

        /*scoreboardba iras*/

    }
    //return 0;
}
