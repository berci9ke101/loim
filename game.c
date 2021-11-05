#include "game.h"
#include "econio.h"
#include "draw.h"
#include "functions.h"
#include <stdio.h>

/*kerdesek kiirasa jobbra*/
/*void rewards(int questionnum)
{
    if (questionnum == 1)
    {
        econio_gotoxy()
    }
    else
    {

    }
}*/

/*jatek inicializalo fuggveny*/
void game_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //clock
    econio_gotoxy(0,2);
    printf("╠═════╝");
    econio_gotoxy(6,1);
    printf("║");
    econio_gotoxy(6, 0);
    printf("╦");

    //kerdesek

}
