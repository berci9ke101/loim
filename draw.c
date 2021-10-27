#include "draw.h"
#include "econio.h"
#include <stdio.h>

/*fuggoleges kozepre igazito*/
int vert_align(int window_width, int rectangle_width)
{
    return ((window_width - 1) / 2) - ((rectangle_width - 1) / 2);
}

/*vizszintes kozepre igazito*/
int hor_align(int window_height, int rectangle_height)
{
    return ((window_height - 1) / 2) - ((rectangle_height - 1) / 2);
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
