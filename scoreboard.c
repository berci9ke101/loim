#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "scoreboard.h"
#include "econio.h"
#include "draw.h"
#include "debugmalloc.h"

#define FILENAME "../scoreboard.loim"

/*fajl kiiratasa a konzolba*/
void scoreboard_print_to_console(void)
{
    //fajl betoltese
    FILE *file;
    file = fopen(FILENAME, "r");
    char buffer[255];

    //jelenlegi sor, a sorok kozti tavolsag es a max sorszam valtozoi
    int linenum = 1; //a jelenlegi sor sorszama
    int spacer = 0; //a tavolsag 0-rol indul, majd kettesevel novekszik
    int max_line_count;
    int filecount = count_lines(FILENAME);
    if (filecount > 8)
    {
        max_line_count = 8;
    }
    else
    {
        max_line_count = filecount;
    } //max 8 a dicsosegtabla  bejegyzeseinek szamas

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count) //osszes sor kiirasa,
        {
            //beolvasott szoveg maximalis hossza
            char name[20 + 1];
            char time[8 + 1];
            char amount[10 + 1];

            if (fgets(buffer, 255, file) == NULL)
            {
                break;
            }

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
        econio_clrscr();
        perror("Dicsőségtábla fájl hiányzik."); //hiba eseten kilepes adott hibakoddal
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

        if (key == KEY_TAB) //help
        {
            help_screen(false);
        }
        else if (key == KEY_ENTER)
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

/*az osszes bemenet beolvasasa, rendezese, majd kiirasa a scoreboardba*/
void read_sort_write(void)
{
    FILE *file;
    file = fopen(FILENAME, "r");
    int linenum = 0;
    int maxlinecount = count_lines(FILENAME);

    char **entries = (char **) malloc((maxlinecount - 1) * sizeof(char *));

    /*az osszes sor beolvasasa a scoreboardbol*/
    if (file)
    {
        do
        {
            int index = 0;
            char *string;
            char *newstring;
            string = (char *) malloc(sizeof(char));

            /*hibakezeles*/
            if (!string)
            {
                free(entries);
                econio_clrscr();
                perror("Nem sikerült memoriát foglalni a dicsőségtáblának!");
                exit(-5);
            }
            do
            {
                index++;
                string[index - 1] = fgetc(file);
                newstring = (char *) malloc((index + 1) * sizeof(char));

                /*hibakezeles*/
                if (!newstring)
                {
                    free(entries);
                    free(string);
                    econio_clrscr();
                    perror("Nem sikerült memoriát foglalni a dicsőségtábla egyik elemének!");
                    exit(-3);
                }

                for (int i = 0; i < index; i++)
                {
                    newstring[i] = string[i];
                }
                free(string);
                string = newstring;
            } while (string[index - 1] != '\n');

            string[index - 1] = '\0';

            entries[linenum] = string;

            linenum++;
        } while (linenum != (maxlinecount - 1));

        fclose(file);
    }
    else
    {
        econio_clrscr();
        perror("Dicsőségtábla fájl hiányzik."); //hiba eseten kilepes adott hibakoddal
        exit(-1);
    }

    SCOREBOARD **score_array = (SCOREBOARD **) malloc((maxlinecount - 1) * sizeof(SCOREBOARD *));

    for (int i = 0; i < (maxlinecount - 2); i++)
    {
        SCOREBOARD *temp = (SCOREBOARD *) malloc(sizeof(SCOREBOARD));
        char name[20 + 1];
        int hour;
        int minute;
        int second;
        char amount[10 + 1];

        sscanf(entries[i], "%[^;];%d:%d:%d;%[^\n]", &name, &hour, &minute, &second, &amount);
        free(entries[i]);

        strcpy(temp->name, name);
        temp->hour = hour;
        temp->minute = minute;
        temp->second = second;
        strcpy(temp->winamount, amount);

        score_array[i] = temp;
    }
    free(entries);

}

/*kiiras a scoreboardba*/
void write_to_scoreboard(char *string)
{
    FILE *file;
    file = fopen(FILENAME, "a");
    if (file)
    {
        /*file vegere ugras (utolso elotti elotti ("ez a \n karakter") karakter, mert az utolso az az EOF)*/
        fseek(file, -1, SEEK_END);

        /*string beirasa a fajl vegere*/
        fprintf(file, "%s\n", string);

        fclose(file);
    }
    else
    {
        econio_clrscr();
        perror("Dicsőségtábla fájl hiányzik."); //hiba eseten kilepes adott hibakoddal
        exit(-1);
    }
}