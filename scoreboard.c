#include <stdio.h>
#include "scoreboard.h"
#include "functions.h"
#include "econio.h"
#include "draw.h"
#include "main_menu.h"
#include <stdlib.h>

/*fajl kiiratasa a konzolba*/
void scoreboard_print_to_console(void)
{
    char name[20 + 1];
    char time[5 + 1];
    char amount[10 + 1];

    //fajl betoltese
    FILE *file;
    file = fopen("../scoreboard.txt", "r");
    char buffer[255];

    //jelenlegi sor, a sorok kozti tavolsag es a max sorszam valtozoi
    int linenum = 1;
    int spacer = 0;
    int max_line_count = count_lines("../scoreboard.txt");

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count)
        {
            fgets(buffer, 255, file);
            sscanf(buffer, "%[^;];%[^;];%[^\n]", name, time, amount);


            name[20] = '\0';
            time[5] = '\0';
            amount[10] = '\0';


            econio_gotoxy(28, (6 + spacer));
            printf(" %d. %s", linenum, name);

            econio_gotoxy(57, (6 + spacer));
            printf("%s", time);

            econio_gotoxy(72, (6 + spacer));
            text_left_align(amount, 18);

            spacer += 2;
            linenum++;
        }
        fclose(file);
    }
    else
    {
        perror("");
    }
}

void scoreboard_init(void)
{
    //kepernyo torlese
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

/*bemeneti gombokkal foglallkozo fuggveny*/
void scoreboard_buttons(void)
{
    while (1)
    {
        int key = econio_getch();
        econio_flush();

        if (key == KEY_ENTER)
        {
            main_menu_init();
            break;
        }

    }
}