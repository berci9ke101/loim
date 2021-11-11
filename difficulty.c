#include "difficulty.h"
#include "econio.h"
#include "draw.h"
#include "functions.h"
#include <stdio.h>
#include "debugmalloc.h"

void difficulty_state_switcher(int state)
{
    //felso allas, X kirajzolasa csak az elso opciohoz
    if (state == 0)
    {
        econio_gotoxy((vert_align(119, 10) + 1), 10);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 11) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 9) + 1), 14);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 16);
        printf("%c", ' ');

    }
        //kozepso allas, X kirajzolasa csak a masodik opciohoz
    else if (state == -1)
    {
        econio_gotoxy((vert_align(119, 10) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 12);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 9) + 1), 14);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 16);
        printf("%c", ' ');
    }
        //also allas, X kirajzolasa csak a harmadik opciohoz
    else if (state == -2)
    {
        econio_gotoxy((vert_align(119, 10) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 9) + 1), 14);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 11) + 1), 16);
        printf("%c", ' ');
    }
    else if (state == -3)
    {
        econio_gotoxy((vert_align(119, 10) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 9) + 1), 14);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 16);
        printf("%c", 'X');
    }

}

void difficulty_buttons(int *global_state, int *difficulty)
{
    int difficulty_state = 0; //legfelso menuallas beallitasa

    /*
     *  menuallas valtozo 3 allapota:
     *
     *   0 - konnyu opcio
     *  -1 - kozepes opcio
     *  -2 - nehez opcio
     *  -3 - kilepes kivalasztva
     *
     * */

    while (1)
    {
        int key = econio_getch(); //lenyomott gomb bekerese
        econio_flush(); //folyekonyabb kirajzolas

        if (key == KEY_UP) //felfele nyilacska lenyomasa
        {
            if (difficulty_state >= -3 && difficulty_state < 0)
            {
                difficulty_state++; //menuallas valtozo leptetese
            }
        }
        else if (key == KEY_DOWN) //lefele nyilacska lenyomasa eseten
        {
            if (difficulty_state > -3 && difficulty_state <= 0)
            {
                difficulty_state--; //menuallas valtozo leptetese
            }
        }
        else if (key == KEY_ENTER) //enter lenyomasa eseten
        {
            if (difficulty_state == 0) //konnyu opcio
            {
                *difficulty = 0;
                break;
            }
            if (difficulty_state == -1) //kozepes opcio
            {
                *difficulty = 1;
                break;
            }
            if (difficulty_state == -2) //nehez opcio
            {
                *difficulty = 2;
                break;
            }

            if (difficulty_state == -3) //vissza
            {
                *global_state = 0;
                break;
            }
        }

        difficulty_state_switcher(difficulty_state); //valtoztatott menu kirajzolasa

    }
}

void difficulty_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //main menu frame
    draw_rect_char_UTF8(vert_align(119, 29), 8, 29, 11, "═", "║", "╔", "╗", "╚", "╝");

    //DOFFICULTY
    econio_gotoxy(vert_align(119, 29), 3);
    printf("N e h é z s é g i  s z i n t ");

    //easy
    econio_gotoxy(vert_align(119, 10), 10);
    printf("(X) Könnyű");

    //normal
    econio_gotoxy(vert_align(119, 11), 12);
    printf("( ) Közepes");

    //hard
    econio_gotoxy(vert_align(119, 9), 14);
    printf("( ) Nehéz");

    //exit
    econio_gotoxy(vert_align(119, 11), 16);
    printf("( ) Vissza");

}
