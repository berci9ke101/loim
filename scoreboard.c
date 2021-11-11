#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "scoreboard.h"
#include "econio.h"
#include "draw.h"
#include "debugmalloc.h"

/*fajl kiiratasa a konzolba*/
void scoreboard_print_to_console(void)
{
    //beolvasott szoveg maximalis hossza
    char name[20 + 1];
    char time[8 + 1];
    char amount[10 + 1];

    //fajl betoltese
    FILE *file;
    file = fopen("../scoreboard.txt", "r");
    char buffer[255];

    //jelenlegi sor, a sorok kozti tavolsag es a max sorszam valtozoi
    int linenum = 1; //a jelenlegi sor sorszama
    int spacer = 0; //a tavolsag 0-rol indul, majd kettesevel novekszik
    int max_line_count = 8; //8 a dicsosegtabla  bejegyzeseinek szamas

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count) //osszes sor kiirasa,
        {
            fgets(buffer, 255, file);
            sscanf(buffer, "%[^;];%[^;];%[^\n]", name, time, amount);

            //a kategoriak meretre "apritasa"
            name[20] = '\0';
            time[8] = '\0';
            amount[10] = '\0';

            //nev "rublika"
            econio_gotoxy(28, (6 + spacer));
            printf(" %d. %s", linenum, name);

            //ido "rublika"
            econio_gotoxy(55, (6 + spacer));
            printf("%s", time);

            //nyeremeny "rublika"
            econio_gotoxy(72, (6 + spacer));
            printf("%*s", 15, amount);
            printf(" Ft");

            //sorok kozti tavolsag es a sorszam novelese
            spacer += 2;
            linenum++;
        }
        fclose(file); //fajl bezarasa
    }
    else
    {
        perror("Scoreboard file error."); //hiba eseten kilepes adott hibakoddal
        exit(-1);
    }
}

/*bemeneti gombokkal foglallkozo fuggveny*/
void scoreboard_buttons(int *global_state)
{
    while (1)
    {
        int key = econio_getch(); //a megnyomott gomb bekerese
        econio_flush(); //folyekonyabb kirajzolas

        if (key == KEY_ENTER)
        {
            *global_state = 0; //a globalis menuvaltozo fomenure (0)-ra valo allitasa
            break;
        }

    }
}

/*dicsosegtabla inicializalasa*/
void scoreboard_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

    //debug mode
#ifdef DEBUG
    console_debug(119, 25);
#endif

    //keret
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");
    draw_rect_char_UTF8(vert_align(119, 67), hor_align(25, 21), 67, 21, "═", "║", "╔", "╗", "╚", "╝");

    //felirat
    econio_gotoxy(vert_align(119, 25), 4);
    printf("D i c s ő s é g t á b l a");

    //adatok kiirasa
    scoreboard_print_to_console();

    //menu megrajzolasa
    econio_gotoxy(4, hor_align(25, 1));
    printf("(X) Vissza");

}