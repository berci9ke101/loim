#include <stdio.h>
#include <windows.h>
#include "econio.h"
#include "functions.h"
#include "draw.h"

/*konzol oszlopok jelolese*/
void console_debug(int width, int height)
{
    econio_clrscr();
    econio_gotoxy(0, 0);
    for (int k = 0; k < height; k++)
    {
        for (int i = 0; i < width; i++)
        {
            if ((i % 10) == 5)
            {
                econio_textcolor(COL_MAGENTA);
                printf("%d", i % 10);
            }
            else if ((i % 10) == 0)
            {
                econio_textcolor(COL_CYAN);
                printf("%d", i % 10);
            }
            else
            {
                econio_textcolor(COL_WHITE);
                printf("░");
            }
        }
    }

    //cross
    econio_textcolor(COL_WHITE);
    for (int y = 0; y < height; y++)
    {
        econio_gotoxy(vert_align(119, 1), y);
        printf("█");
    }
    for (int x = 0; x < width; x++)
    {
        econio_gotoxy(x, hor_align(25, 1));
        printf("█");
    }

}

/*konzolablak elnevezese es meretenek megvaltoztatasa*/
void console_init(void)
{
    system("mode con:cols=119 lines=25");
    econio_set_title("LOIM");
    SetConsoleOutputCP(CP_UTF8);
    econio_rawmode();
    econio_kbhit();
}

/*sorok megszamolasa egy fajlban*/
int count_lines(char *file_name)
{
    //fajl megnyitasa
    FILE *file;
    file = fopen(file_name, "r");
    char c;
    int max_line_count = 1;

    //karakter beolvasas a fajl vege karakterig
    while (c != EOF)
    {
        c = getc(file);
        if (c == '\n')
        {
            max_line_count++;
        }
    }
    fclose(file);

    //visszateres a sorok szamaval
    return max_line_count;
}

/*fajl kiiratasa a konzolba*/
void scoreboard_print_to_console(void)
{
    char name[22];
    char time[22];
    char amount[22];

    //fajl betoltese
    FILE *file;
    file = fopen("../scoreboard.txt", "r");
    char buffer[255];

    //jelenlegi sor es a max sorszam valtozoi
    int linenum = 1;
    int max_line_count = count_lines("../scoreboard.txt");

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count)
        {
            fgets(buffer, 255, file);
            sscanf(buffer, "%[^;];%[^;];%[^\n]", name, time, amount);

            econio_gotoxy(28, (3+linenum));
            printf("%s", name);

            econio_gotoxy(50, (3+linenum));
            printf("%s", time);

            econio_gotoxy(72, (3+linenum));
            printf("%s", amount);
            linenum++;
        }
        fclose(file);
    }
    else
    {
        perror("");
    }
}

void scoreboard()
{
    //kepernyo torlese
    econio_clrscr();

    //keret
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");
    draw_rect_char_UTF8(vert_align(119, 67), hor_align(25, 21), 67, 21, "═", "║", "╔", "╗", "╚", "╝");

    //felirat
    //econio_gotoxy(vert_align(119, 13), 4);
   // printf("Dicsőségtábla");

    //adatok kiirasa
    scoreboard_print_to_console();
}

/*tisztogato fuggveny*/
/*void clean_master_pro_900(void **p)
{

}*/