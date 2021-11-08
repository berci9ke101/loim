#include "functions.h"
#include "main_menu.h"
#include "scoreboard.h"
#include "difficulty.h"
#include "game.h"
#include "draw.h"
#include "timer.h"
#include "question.h"
#include <stdbool.h>
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
    int prev_questionnum = 0;
    int amount = 0;
    int fix_amount = 0;
    bool used_audience = false;
    bool used_half = false;
    QUESTION loim;

    /*MAGA A JATEK*/
    game_init(); //felhasznaloi felulet kirajzolasa es a jatek inicializalasa

    while (1)
    {
        econio_flush(); //folyekonyabb kirajzolas
        /*TIMER*/
        print_time(hour, minute, second); //ido kiiratasa
        prev_time = timer(prev_time, &hour, &minute, &second); //maga a timer fuggvenye

        /*oldalso nyeremeny tablazat frissitese*/
        econio_sleep(0.001); //hogy ne villodzon a kirajzolt nyilacska
        arrow_and_reward(questionnum, &amount, &fix_amount); //nyilacska kirajzolasa a jelnlegi kerdes alapjan

        /*kerdes es valaszok betoltese, kiirasa*/
        if (questionnum != prev_questionnum)
        {
            loim = load_question_by_difficulty(diffselect(difficulty)); //random kerdes betoltese nehezseg alapjan

            /*kerdes es valaszok kirajzolasa*/
            print_question(loim);

#ifdef DEBUG
            print_cheat(loim);
#endif

            free_QUESTION(loim);

            prev_questionnum = questionnum;
        }


        /*vezerles*/
        int key; //lenyomott billentyű változója

        if (econio_kbhit())
        {
            key = econio_getch(); //lenyomott gomb bekérése, ha tortent billentyulenyomas
        }

        /*A valasztasa*/
        if (key == 97)
        {
            if (strcmp(loim.answer, "A") == 0)
            {
                questionnum++;
            }
            else
            {
                exit(0);
            }
        }

            /*B valasztasa*/
        else if (key == 98)
        {
            if (strcmp(loim.answer, "B") == 0)
            {
                questionnum++;
            }
            else
            {
                exit(0);
            }
        }

            /*C valasztasa*/
        else if (key == 99)
        {
            if (strcmp(loim.answer, "C") == 0)
            {
                questionnum++;
            }
            else
            {
                exit(0);
            }
        }

            /*D valasztasa*/
        else if (key == 100)
        {
            if (strcmp(loim.answer, "D") == 0)
            {
                questionnum++;
            }
            else
            {
                exit(0);
            }
        }

            /*K valasztasa*/
        else if (key == 107)
        {
            if (!used_audience)
            {
                draw_audience(loim.answer);
                used_audience = true;
                econio_gotoxy(3, 22);
                printf("                      ");
            }
        }

            /*F valasztasa*/
        else if (key == 102)
        {
//            if (!used_half)
//            {
//                half();
//                used_half = true;
//            }
        }

            /*kilepeskor a nev megadasa*/
        else if (key == KEY_ESCAPE)
        {
            econio_gotoxy(0, 0);
            printf("%02d:%02d:%02d", hour, minute, second);
            econio_sleep(1);
            system("NAGYHF.exe");
            return 0;
        }

        key = KEY_UNKNOWNKEY; //ha nincs input, akkor ismeretlen billentyűre állítás

        /*scoreboardba iras*/


    }
    //return 0;
}
