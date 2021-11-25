#include <stdio.h>
#include "econio.h"
#include "functions.h"
#include "draw.h"
#include "debugmalloc.h"

#ifdef _WIN32

#include <windows.h>

#endif


/*string integerre valtoztatasa*/
int string_to_int(char *string)
{
    int len = (int) strlen(string);
    char *copy = (char *) malloc((len + 1) * sizeof(char));
    strcpy(copy, string);

    for (int i = 0; i < len + 1; i++)
    {
        if (copy[i] == ' ')
        {
            for (int k = i; k < len; k++)
            {
                copy[k] = copy[k + 1];
            }
        }
    }
    int num = atoi(copy);
    free(copy);
    return num;
}

/*dicsosegtabla precedencia*/
int prec(SCOREBOARD **a, SCOREBOARD **b)
{
    if (string_to_int((*a)->winamount) == string_to_int((*b)->winamount))
    {
        return ((*a)->hour * 3600 + (*a)->minute * 60 + (*a)->second) >
               ((*b)->hour * 3600 + (*b)->minute * 60 + (*b)->second) ? 1 : 0;
    }
    return string_to_int((*a)->winamount) < string_to_int((*b)->winamount) ? 1 : 0;
}

/*scoreboard bubble sort*/
void scoreboard_sort(SCOREBOARD **array, int maxlinecount)
{
    qsort(array, maxlinecount, sizeof(SCOREBOARD *), (int (*)(const void *, const void *)) prec);
}

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
void hidecursor(void)
{
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &(CONSOLE_CURSOR_INFO) {1, FALSE});
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
#ifdef _WIN32
    system("mode con:cols=119 lines=25");
    UINT original_cp = GetConsoleCP();
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTitle("Legyen Ön Is Milliomos");
    SetConsoleCP(original_cp);
    hidecursor();
#endif
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
            c = (char) getc(file);
            if (c == '\n')
            {
                max_line_count++;
            }
        }
        fclose(file);
    }
    else
    {
        econio_clrscr();
        perror("Sorok megszámlálása sikertelen."); //hiba eseten kilepes adott hibakoddal
        exit(-2);
    }

    //visszateres a sorok szamaval
    return max_line_count;
}

/*a nyeremeny tagolassal valo stringhssozanak kiszamitasa*/
int calc_win_amount_length(int win_amount)
{
    int size;
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

    size = num_thous + num_num + 1; //az osszes ertek osszeadasa +1 a lezáró nulla

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
    int size = (int) strlen(string);

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
    if (number == 0)
    {
        char *returnstring = malloc((1 + 1) * sizeof(char));
        returnstring[0] = '0';
        returnstring[1] = '\0';
        return returnstring;
    }
    else
    {
        int size = calc_win_amount_length(number);
        int helpnum;

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
}

/*help function*/
void help_screen(bool isgame)
{
    int x, y, w, h;

    if (isgame)
    {
        x = 88;
        y = 20;
        w = 31;
        h = 5;
    }
    else
    {
        x = 0;
        y = 0;
        w = 31;
        h = 5;
    }

    //frame
    draw_rect_char_UTF8(x, y, w, h, "═", "║", "╔", "╗", "╚", "╝");

    /*help text*/
    if (isgame)
    {
        econio_gotoxy(x + 1, y + 1);
        printf("(TAB)          Segítség ablak");

        econio_gotoxy(x + 1, y + 2);
        printf("(A/B/C/D) Kérdés kiválasztása");

        econio_gotoxy(x + 1, y + 3);
        printf("(ESC)                Megállás");

        econio_gotoxy(118, 20);
        printf("╣");

        econio_gotoxy(88, 24);
        printf("╩");
    }
    else
    {
        econio_gotoxy(x + 1, y + 1);
        printf("(TAB)          Segítség ablak");

        econio_gotoxy(x + 1, y + 2);
        printf("(FEL/LE)     Kurzor mozgatása");

        econio_gotoxy(x + 1, y + 3);
        printf("(Enter)    Opció kiválasztása");

        econio_gotoxy(30, 0);
        printf("╦");

        econio_gotoxy(0, 4);
        printf("╠");
    }

}