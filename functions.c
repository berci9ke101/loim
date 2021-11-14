#include <stdio.h>
#include <windows.h>
#include "econio.h"
#include "functions.h"
#include "draw.h"
#include "debugmalloc.h"

/*bubble sort*/
void bubble_sort(int size, int *array)
{
    int i, j, temp;
    for (i = 0; i < (size - 1); i++)
    {
        for (j = 0; j < (size - 1 - i); j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }

        }
    }
}

/*kurzor elrejtese*/
/*forras: https://stackoverflow.com/a/30126700*/
void hidecursor(void)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

/*konzol oszlopok jelolese debug szempontbol*/
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
    hidecursor();
    econio_rawmode();
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
    if (file)
    {
        while (c != EOF)
        {
            c = getc(file);
            if (c == '\n')
            {
                max_line_count++;
            }
        }
        fclose(file);
    }
    else
    {
        perror("Sorok megszámlálása sikertlen."); //hiba eseten kilepes adott hibakoddal
        exit(-2);
    }

    //visszateres a sorok szamaval
    return max_line_count;
}

/*a nyeremeny tagolassal valo stringhssozanak kiszamitasa*/
int calc_win_amount_length(int win_amount)
{
    int size = 0;
    int num_thous = 0;
    int num_num = 0;
    int copy = win_amount;

    /*felosztas megszamolasa*/
    while (win_amount > 1000)
    {
        win_amount /= 1000;
        num_thous++;
    }

    /*karakterek megszamolasa*/
    while (copy > 0)
    {
        copy /= 10;
        num_num++;
    }

    size = num_thous + num_num + 2; //az osszes ertek osszeadasa es a "Ft" szamolasa a vegen

    return size;
}

/*szam felosztasa es kiirasa rekurzivan*/
void split_num(int number)
{
    if (number < 1000)
    {
        printf("%d", number);
    }
    else
    {
        split_num(number / 1000);
        printf(" %03d", number % 1000);
    }
}

/*egy sztring megforditasa*/
void reverse_string(char *string)
{
    int size = strlen(string);

    for (int i = 0; i < size / 2; i++)
    {
        char temp = string[i];
        string[i] = string[size - i - 1];
        string[size - i - 1] = temp;
    }
}

/*egy szam tagolasa a jobb olvashatosag jegyeben pl: "2000" helyett "2 000"*/
char *split_up_num(int number)
{
    int size = calc_win_amount_length(number);
    int helpnum = 0;

    char *returnstring = malloc((size + 1) * sizeof(char));
    char help[5 + 1];

    returnstring[0] = '\0';

    while (number != 0)
    {
        helpnum = (number % 1000);
        number /= 1000;

        if (number != 0)
        {
            sprintf(help, " %03d", helpnum);
        }
        else
        {
            sprintf(help, "%d", helpnum);
        }

        reverse_string(help);

        strcat(returnstring, help);
    }
    returnstring[size] = '\0';

    reverse_string(returnstring);
    return returnstring;
}

/*help function*/
void help_screen(int x, int y)
{
    draw_rect_char_UTF8((vert_align(119, 11) - 59) + x, (hor_align(25, 11) - 12) + y, 119, 25, "═", "║", "╔", "╗", "╚",
                        "╝");
    econio_gotoxy();
}