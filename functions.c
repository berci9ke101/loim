#include <stdio.h>
#include <windows.h>
#include "econio.h"
#include "functions.h"

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
void print_to_console(char *file_name)
{
    //fajl betoltese
    FILE *file;
    file = fopen(file_name, "r");
    char buffer[255];

    //jelenlegi sor es a max sorszam valtozoi
    int linenum = 1;
    int max_line_count = count_lines(file_name);

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count)
        {
            fgets(buffer, 255, file);
            printf("%s", buffer);
            linenum++;
        }
        fclose(file);
    }
    else
    {
        perror("");
    }
}

/*konzolablak elnevezese es meretenek megvaltoztatasa*/
void init_console_window(void)
{
    system("mode con:cols=119 lines=25");
    econio_set_title("LOIM");
    SetConsoleOutputCP(CP_UTF8);
    econio_rawmode();
    econio_kbhit();
}


/*konzol oszlopok jelolese*/
void debug_console(int width, int height)
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

/*teglalap rajzolo fuggveny tetszoleges karakterekkel(UTF-8)*/
void draw_rect_char_UTF8(int x, int y, int width, int height, char *hor, char *vert, char *t_left, char *t_right,
                         char *b_left, char *b_right)
{

    for (int i = 0; i < width - 1; i++)
    {
        econio_gotoxy(x + i, y);
        printf("%s", hor);
        econio_gotoxy(x + i, y + height - 1);
        printf("%s", hor);

    }

    for (int i = 0; i < height - 1; i++)
    {
        econio_gotoxy(x, y + i);
        printf("%s", vert);
        econio_gotoxy(x + width - 1, y + i);
        printf("%s", vert);
    }


    econio_gotoxy(x, y);
    printf("%s", t_left);
    econio_gotoxy(x + width - 1, y);
    printf("%s", t_right);
    econio_gotoxy(x, y + height - 1);
    printf("%s", b_left);
    econio_gotoxy(x + width - 1, y + height - 1);
    printf("%s", b_right);
}

void init_main_menu(void)
{
    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //main menu frame
    draw_rect_char_UTF8(vert_align(119, 29), hor_align(25, 9), 29, 9, "═", "║", "╔", "╗", "╚", "╝");

    //LOIM
    econio_gotoxy(vert_align(119, 23), 3);
    printf("Legyen Ön Is Milliomos!");

    //start game
    econio_gotoxy(vert_align(119, 17), 10);
    printf("(X) Játék kezdése");

    //scoreboard
    econio_gotoxy(vert_align(119, 17), 12);
    printf("( ) Dicsőségtábla");

    //exit
    econio_gotoxy(vert_align(119, 11), 14);
    printf("( ) Kilépés");

}

/*tisztogato fuggveny*/
/*void clean_master_pro_900(void **p)
{

}*/