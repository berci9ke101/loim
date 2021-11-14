#include "draw.h"
#include "econio.h"
#include "functions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

/*szazalek ertek atvaltasa blokkokba*/
char *percent_block(int number)
{
    number /= 10;
    switch (number)
    {
        case 0:
            return "▒";
        case 1:
            return "▒▒";
        case 2:
            return "▒▒▒";
        case 3:
            return "▒▒▒▒";
        case 4:
            return "▒▒▒▒▒";
        case 5:
            return "▒▒▒▒▒▒";
        case 6:
            return "▒▒▒▒▒▒▒";
        case 7:
            return "▒▒▒▒▒▒▒▒";
        case 8:
            return "▒▒▒▒▒▒▒▒▒";
        case 9:
            return "▒▒▒▒▒▒▒▒▒▒";
        default:
            return "";
    }
}

/*kozonseg velemenye eltuntetese*/
void del_audience(void)
{
    for (int i = 0; i < 6; i++)
    {
        econio_gotoxy(2, 9 + i);
        printf("               ");
    }
}

/*kozonseg velemenye*/
void draw_audience(char *answer)
{
    int nums[4] = {rand() % 100, rand() % 100, rand() % 100, rand() % 100}; //random szamok generalasa

    bubble_sort(4, nums); //szamok rendezese novekvo sorrendbe

    econio_gotoxy(2, 9);
    printf("K ö z ö n s é g");

    econio_gotoxy(2, 11);
    printf("A");
    econio_gotoxy(2, 12);
    printf("B");
    econio_gotoxy(2, 13);
    printf("C");
    econio_gotoxy(2, 14);
    printf("D");

    if (strcmp(answer, "A") == 0)
    {
        econio_gotoxy(4, 11);
        printf("%s%d", percent_block(nums[3]), nums[3]);
        econio_gotoxy(4, 12);
        printf("%s%d", percent_block(nums[1]), nums[1]);
        econio_gotoxy(4, 13);
        printf("%s%d", percent_block(nums[0]), nums[0]);
        econio_gotoxy(4, 14);
        printf("%s%d", percent_block(nums[2]), nums[2]);
    }
    else if (strcmp(answer, "B") == 0)
    {
        econio_gotoxy(4, 11);
        printf("%s%d", percent_block(nums[1]), nums[1]);
        econio_gotoxy(4, 12);
        printf("%s%d", percent_block(nums[3]), nums[3]);
        econio_gotoxy(4, 13);
        printf("%s%d", percent_block(nums[0]), nums[0]);
        econio_gotoxy(4, 14);
        printf("%s%d", percent_block(nums[2]), nums[2]);
    }
    else if (strcmp(answer, "C") == 0)
    {
        econio_gotoxy(4, 11);
        printf("%s%d", percent_block(nums[0]), nums[0]);
        econio_gotoxy(4, 12);
        printf("%s%d", percent_block(nums[1]), nums[1]);
        econio_gotoxy(4, 13);
        printf("%s%d", percent_block(nums[3]), nums[3]);
        econio_gotoxy(4, 14);
        printf("%s%d", percent_block(nums[2]), nums[2]);
    }
    else if (strcmp(answer, "D") == 0)
    {
        econio_gotoxy(4, 11);
        printf("%s%d", percent_block(nums[1]), nums[1]);
        econio_gotoxy(4, 12);
        printf("%s%d", percent_block(nums[2]), nums[2]);
        econio_gotoxy(4, 13);
        printf("%s%d", percent_block(nums[0]), nums[0]);
        econio_gotoxy(4, 14);
        printf("%s%d", percent_block(nums[3]), nums[3]);
    }
}

/*kerdesek megfelezese*/
void half(QUESTION loim)
{
    if (strcmp(loim.answer, "A") == 0)
    {
        del_question("B");
        del_question("D");
    }
    else if (strcmp(loim.answer, "B") == 0)
    {
        del_question("A");
        del_question("D");
    }
    else if (strcmp(loim.answer, "C") == 0)
    {
        del_question("B");
        del_question("D");
    }
    else if (strcmp(loim.answer, "D") == 0)
    {
        del_question("A");
        del_question("C");
    }
}

/*egyik kerdes eltuntetese*/
void del_question(char *ABCD)
{
    if (strcmp(ABCD, "A") == 0)
    {
        econio_gotoxy(17, 12);
        for (int i = 1; i <= 35; i++)
        {
            printf(" ");
        }
    }
    else if (strcmp(ABCD, "B") == 0)
    {
        econio_gotoxy(17, 13);
        for (int i = 1; i <= 35; i++)
        {
            printf(" ");
        }
    }
    else if (strcmp(ABCD, "C") == 0)
    {
        econio_gotoxy(52, 12);
        for (int i = 1; i <= 35; i++)
        {
            printf(" ");
        }
    }
    else if (strcmp(ABCD, "D") == 0)
    {
        econio_gotoxy(52, 13);
        for (int i = 1; i <= 35; i++)
        {
            printf(" ");
        }
    }
}

/*nyilak kitorlese*/
void del_arrows(void)
{
    int k = 1;
    for (int i = 17; i >= 1; i--)
    {
        if (i != 6 && i != 12)
        {
            econio_gotoxy(102, i);
            printf("  ");
        }
    }
}

/*fuggoleges kozepre igazito*/
int vert_align(int window_width, int rectangle_width)
{
    //visszaadja honnan kellene elkezdeni kiirni adott hosszusagu szoveget, ha fuggolegesen kozepre szeretnenk igazitani
    return ((window_width - 1) / 2) - ((rectangle_width - 1) / 2);
}

/*vizszintes kozepre igazito*/
int hor_align(int window_height, int rectangle_height)
{
    //visszaadja honnan kellene elkezdeni kiirni adott hosszusagu szoveget, ha vizszintesen kozepre szeretnenk igazitani
    return ((window_height - 1) / 2) - ((rectangle_height - 1) / 2);
}

/*teglalap rajzolo fuggveny tetszoleges karakterekkel(UTF-8), tetszoleges kezdoponttol(bal felso sarka a teglalapnak)*/
/*azert string, mert nehany UTF-8 karakter nem fer bele az alapertelmezett c karaktermeretbe*/
void draw_rect_char_UTF8(int x, int y, int width, int height, char *hor, char *vert, char *t_left, char *t_right,
                         char *b_left, char *b_right)
{

    //kirajzolja a vizszintes hatarolo karaktereket a teglalap "aljan" es "tetjen"
    for (int i = 0; i < width - 1; i++)
    {
        econio_gotoxy(x + i, y);
        printf("%s", hor);
        econio_gotoxy(x + i, y + height - 1);
        printf("%s", hor);

    }

    //kirajzolja a fuggoleges hatarolo karaktereket a teglalap "jobb" es "bal" oldalan
    for (int i = 0; i < height - 1; i++)
    {
        econio_gotoxy(x, y + i);
        printf("%s", vert);
        econio_gotoxy(x + width - 1, y + i);
        printf("%s", vert);
    }

    //bal felso hatarolo karakter kirajzolasa
    econio_gotoxy(x, y);
    printf("%s", t_left);

    //jobb felso hatarolo karakter kirajzolasa
    econio_gotoxy(x + width - 1, y);
    printf("%s", t_right);

    //bal also hatarolo karakter kirajzolasa
    econio_gotoxy(x, y + height - 1);
    printf("%s", b_left);

    //jobb also hatarolo karakter kirajzolasa
    econio_gotoxy(x + width - 1, y + height - 1);
    printf("%s", b_right);
}
