//
// Function source file
//
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
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
    system("mode con:cols=120 lines=25");
    system("title Legyel Te Is Adocsalo");
}

/*karakter olvasasa portolas miatt*/
char char_read(void)
{
    //beolvassa a karakter (ASCII tabla)
    return getch();
}

/*bemeneti gombokkal foglallkozo fuggveny*/
void buttons(void)
{
    bool exit = false;

    while (!exit)
    {
        switch (char_read())
        {
            //bemenetek gombjai, amik fuggvenyeket hivnak meg.
            case '3':
                print_to_console("../UI/MENU1.txt");
                break;
            case '2':
                print_to_console("../UI/MENU2.txt");
                break;
            case 'e':
                exit = true;
                break;
        }
    }
}

/*teglalap rajzolo fuggveny tetszoleges karakterekkel*/
void draw_rect_char(int x, int y, int width, int height, char *symb)
{
    char hor = symb[0];
    char vert = symb[1];
    char t_left = symb[2];
    char t_right = symb[3];
    char b_left = symb[4];
    char b_right = symb[5];

    for (int i = 0; i < width - 1; i++)
    {
        econio_gotoxy(x + i, y);
        printf("%c", hor);
        econio_gotoxy(x + i, y + height - 1);
        printf("%c", hor);

    }

    for (int i = 0; i < height - 1; i++)
    {
        econio_gotoxy(x, y + i);
        printf("%c", vert);
        econio_gotoxy(x + width - 1, y + i);
        printf("%c", vert);
    }


    econio_gotoxy(x, y);
    printf("%c", t_left);
    econio_gotoxy(x + width - 1, y);
    printf("%c", t_right);
    econio_gotoxy(x, y + height - 1);
    printf("%c", b_left);
    econio_gotoxy(x + width - 1, y + height - 1);
    printf("%c", b_right);
}

/*tisztogato fuggveny*/
/*void clean_master_pro_900(void **p)
{

}*/