#include "draw.h"
#include "econio.h"
#include <stdio.h>
#include <string.h>

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
