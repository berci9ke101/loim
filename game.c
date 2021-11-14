#include "game.h"
#include "econio.h"
#include "draw.h"
#include "timer.h"
#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "debugmalloc.h"

/*"nyertel" kepernyo kirajzolasa*/
void win(int amount)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //szoveg kiirasa
    econio_gotoxy(vert_align(119, 56), hor_align(25, 1) - 1);
    printf("G R A T U L Á L U N K  Ö N  M I L L I O M O S  L E T T !");
    econio_gotoxy(vert_align(119, 28), hor_align(25, 1) + 1);
    printf("Nyereménye : ");
    split_num(amount);
    printf(" Ft");

    //kis varakozas utan tovabblepes a scoreboardra
    econio_sleep(5);
}

/*"vesztettel" kepernyo kirajzolasa*/
void lose(int fix_amount)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //szoveg kiirasa
    econio_gotoxy(vert_align(119, 54), hor_align(25, 1) - 1);
    printf("S A J N O S,  Ö N  N E M  L E T T  M I L L I O M O S !");
    econio_gotoxy(vert_align(119, 28), hor_align(25, 1) + 1);
    printf("Nyereménye : ");
    split_num(fix_amount);
    printf(" Ft");


    //kis varakozas utan tovabblepes a scoreboardra
    econio_sleep(5);
}

/*aktualis kerdes jelzese, illetve a nyeremeny megadasa*/
void arrow_and_reward(int questionnum, int *amount, int *fix_amount)
{
    del_arrows();
    switch (questionnum)
    {
        case 1:
        {
            econio_gotoxy(102, 17);
            printf("->");
            *amount = 0;
            *fix_amount = 0;
            break;
        }
        case 2:
        {
            econio_gotoxy(102, 16);
            printf("->");
            *amount = 10000;
            break;
        }
        case 3:
        {
            econio_gotoxy(102, 15);
            printf("->");
            *amount = 20000;
            break;
        }
        case 4:
        {
            econio_gotoxy(102, 14);
            printf("->");
            *amount = 50000;
            break;
        }
        case 5:
        {
            econio_gotoxy(102, 13);
            printf("->");
            *amount = 100000;
            break;
        }
        case 6:
        {
            econio_gotoxy(102, 11);
            printf("->");
            *amount = 250000;
            *fix_amount = 250000;
            break;
        }
        case 7:
        {
            econio_gotoxy(102, 10);
            printf("->");
            *amount = 500000;
            break;
        }
        case 8:
        {
            econio_gotoxy(102, 9);
            printf("->");
            *amount = 750000;
            break;
        }
        case 9:
        {
            econio_gotoxy(102, 8);
            printf("->");
            *amount = 1000000;
            break;
        }
        case 10:
        {
            econio_gotoxy(102, 7);
            printf("->");
            *amount = 1500000;
            break;
        }
        case 11:
        {
            econio_gotoxy(102, 5);
            printf("->");
            *amount = 2000000;
            *fix_amount = 2000000;
            break;
        }
        case 12:
        {
            econio_gotoxy(102, 4);
            printf("->");
            *amount = 5000000;
            break;
        }
        case 13:
        {
            econio_gotoxy(102, 3);
            printf("->");
            *amount = 10000000;
            break;
        }
        case 14:
        {
            econio_gotoxy(102, 2);
            printf("->");
            *amount = 15000000;
            break;
        }
        case 15:
        {
            econio_gotoxy(102, 1);
            printf("->");
            *amount = 25000000;
            break;
        }
        case 16:
        {
            *amount = 50000000;
            *fix_amount = 50000000;
        }
        default:
            break;
    }
}

/*jatek inicializalo fuggveny*/
void game_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //clock
    econio_gotoxy(0, 2);
    printf("╠════════╝");
    econio_gotoxy(9, 1);
    printf("║");
    econio_gotoxy(9, 0);
    printf("╦");

    //win amount frame and text
    econio_gotoxy(96, 18);
    printf("╚═══╩═════════════════╣");
    econio_gotoxy(96, 12);
    printf("╠═══╬═════════════════╣");
    econio_gotoxy(96, 6);
    printf("╠═══╬═════════════════╣");
    econio_gotoxy(96, 0);
    printf("╦═══╦═════════════════╗");

    char amount[15][11] = {"50 000 000", "25 000 000", "15 000 000", "10 000 000", "5 000 000", "2 000 000",
                           "1 500 000", "1 000 000", "750 000", "500 000", "250 000", "100 000", "50 000", "20 000",
                           "10 000"};

    int k = 1;
    for (int i = 17; i >= 1; i--)
    {
        if (i != 6 && i != 12)
        {
            econio_gotoxy(96, i);
            printf("║%*d.║", 2, k++);
            printf("    %*s Ft", 10, amount[15 - (k - 1)]);
        }
    }

    //help
    econio_gotoxy(3, 21);
    printf("kérdések felezése (F)");
    econio_gotoxy(3, 22);
    printf("közönség véleménye (K)");


}

/*nehezseg sorsolo*/
int diffselect(int difficulty)
{
    switch (difficulty)
    {
        case 0:
            return (rand() % 5 + 1);
        case 1:
            return (rand() % 5 + 6);
        case 2:
            return (rand() % 5 + 11);
        default:
            return (rand() % 5 + 6);
    }
}

/*nev megadasa majd a scoreboardba iras*/
char *give_name(bool stop, int hour, int minute, int second, int amount, int fix_amount)
{
    /*nev bekerese*/
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //szoveg kiirasa
    econio_gotoxy(vert_align(119, 5), hor_align(25, 1) - 1);
    printf("N É V");

    //kis teglalap kirajzolasa
    draw_rect_char_UTF8(vert_align(119, 23), hor_align(25, 5), 23, 5, "═", "║", "╔", "╗", "╚", "╝");

    //kurzor pontos helyre valo mozditasa
    econio_gotoxy(50, 13);
    econio_rawmode();
    char c;
    int max = 0;
    char string[19 + 1];
    do
    {
        if (econio_kbhit())
        {
            c = econio_getch();
            if (c == '\n')
            {
                break;
            }
            putchar(c);
            if ((int) c == 8)
            {
                econio_gotoxy(50 + max, 13);
                if (max != 0)
                {
                    printf(" ");
                }
                econio_gotoxy(50 + max, 13);
                if (max > 0)
                {
                    max--;
                }
            }
            else
            {
                string[max++] = c;
            }
        }
    } while (max != 19);
    string[max] = '\0';
    econio_gotoxy(46, 16);

    if (strlen(string) == 0)
    {
        char string2[] = {"NÉV NÉLKÜL"};
        strcpy(string, string2);
    }

    econio_sleep(4);

    /*kiiras string krealasa*/
    char *output;
    char *outamount;

    int size = 0;
    size += strlen(string); //nev hossza
    size += 8; //timer erteke fix hh:mm:ss

    if (!stop)
    {
        /*fix_amount*/
        size += calc_win_amount_length(fix_amount);
        output = malloc((size + 3) * sizeof(char)); //lezaro nulla es a ket ';' szama = +3
        outamount = split_up_num(fix_amount);
    }
    else
    {
        /*amount*/
        size += calc_win_amount_length(amount);
        output = malloc((size + 3) * sizeof(char)); //lezaro nulla es a ket ';' szama = +3
        outamount = split_up_num(amount);
    }

    sprintf(output, "%s;%d:%d:%d;%s Ft", string, hour, minute, second, outamount);

    free(outamount);
    econio_sleep(4);

    return output;
}

/*gameplay*/
int game(int difficulty)
{
    /*GAME*/

    /*ORA INICIALIZALASA*/
    int hour = 0;
    int minute = 0;
    int second = 0;
    time_t prev_time = time(0);

    /*KERDES VALTOZO, SEGITSEGEK ES A NYERT OSSZEG "NULLAZASA"*/
    int questionnum = 1;
    int prev_questionnum = 0;
    bool stop = false;
    int amount = 0;
    int fix_amount = 0;
    bool used_audience = false;
    bool used_half = false;
    char **questions = load_questions();
    QUESTION loim;

    /*MAGA A JATEK*/
    game_init(); //felhasznaloi felulet kirajzolasa es a jatek inicializalasa

    do
    {
        econio_flush(); //folyekonyabb kirajzolas
        /*TIMER*/
        print_time(hour, minute, second); //ido kiiratasa
        prev_time = timer(prev_time, &hour, &minute, &second); //maga a timer fuggvenye

        /*oldalso nyeremeny tablazat frissitese*/
        econio_sleep(0.001); //hogy ne villodzon a kirajzolt nyilacska
        arrow_and_reward(questionnum, &amount, &fix_amount); //nyilacska kirajzolasa a jelnlegi kerdes alapjan

        if (questionnum >= 16)
        {
            break;
        }

        /*kerdes es valaszok betoltese, kiirasa*/
        if (questionnum != prev_questionnum)
        {
            loim = load_question_by_difficulty(diffselect(difficulty),
                                               questions); //random kerdes betoltese nehezseg alapjan

            /*kerdes es valaszok kirajzolasa*/
            print_question(loim);

#ifdef DEBUG
            print_cheat(loim);
#endif
            del_audience();

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
                break;
            }
            free_QUESTION(loim);
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
                break;
            }
            free_QUESTION(loim);
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
                break;
            }
            free_QUESTION(loim);
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
                break;
            }
            free_QUESTION(loim);
        }

            /*K valasztasa*/
        else if (key == 107)
        {
            if (!used_audience)
            {
                draw_audience(loim.answer);
                used_audience = true;
                econio_gotoxy(3, 22);
                for (int i = 1; i <= 22; i++)
                {
                    printf(" ");
                }
            }
        }

            /*F valasztasa*/
        else if (key == 102)
        {
            if (!used_half)
            {
                half(loim);
                used_half = true;
                econio_gotoxy(3, 21);
                for (int i = 1; i <= 22; i++)
                {
                    printf(" ");
                }
            }
        }

            /*kilepes*/
        else if (key == KEY_ESCAPE)
        {
            stop = true;
            break;
        }

        key = KEY_UNKNOWNKEY; //ha nincs input, akkor ismeretlen billentyűre állítás
    } while (questionnum < 17);

    /*nev megadasa es scoreboardba iras*/

    if (questionnum <= 15)
    {
        free_QUESTION(loim);
    }
    freeup_questions_array(questions);

    if (stop)
    {
        if (questionnum == 1)
        {
            lose(fix_amount);
        }
        else
        {
            win(amount);
        }
    }
    else if (questionnum == 16)
    {
        win(fix_amount);
    }
    else
    {
        lose(fix_amount);
    }

    give_name(stop, hour, minute, second, amount, fix_amount);

//    econio_gotoxy(0, 0);
//    printf("%02d:%02d:%02d", hour, minute, second);
//    econio_sleep(1);
//    exit(0);
//    system("NAGYHF.exe");
}