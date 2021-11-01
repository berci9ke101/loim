#include "econio.h"
#include "main_menu.h"
#include "draw.h"
#include "scoreboard.h"
#include "functions.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void main_menu_state_switcher(int state)
{
    if (state == 0)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');

    }
    else if (state == -1)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');
    }
    else if (state == -2)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", 'X');
    }

}

/*bemeneti gombokkal foglallkozo fuggveny*/
void main_menu_buttons(void)
{
    int main_menu_state = 0;
    while (1)
    {
        int key = econio_getch();
        econio_flush();

        if (key == KEY_UP)
        {
            if (main_menu_state >= -2 && main_menu_state < 0)
            {
                main_menu_state++;
            }
        }
        else if (key == KEY_DOWN)
        {
            if (main_menu_state > -2 && main_menu_state <= 0)
            {
                main_menu_state--;
            }
        }
        else if (key == KEY_ENTER)
        {
            if (main_menu_state == 0)
            {
                state = 2;
                break;
            }
            if (main_menu_state == -1)
            {
                state = 1;
                break;
            }

            if (main_menu_state == -2)
            {
                exit(0);
            }
        }

        main_menu_state_switcher(main_menu_state);

    }
}

void main_menu_init(void)
{
#ifdef DEBUG
    console_debug(119, 25);
#endif

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