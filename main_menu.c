#include "econio.h"
#include "main_menu.h"
#include "draw.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

/*menupont valto fuggveny*/
void main_menu_state_switcher(int state)
{
    //felso allas, X kirajzolasa csak az elso opciohoz
    if (state == 0)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');

    }
        //kozepso allas, X kirajzolasa csak a masodik opciohoz
    else if (state == -1)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');
    }
        //also allas, X kirajzolasa csak a harmadik opciohoz
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
void main_menu_buttons(int *global_state)
{
    int main_menu_state = 0; //legfelso menuallas beallitasa

    /*
     *  menuallas valtozo 3 allapota:
     *
     *   0 - jatek opcio kivalasztva
     *  -1 - nehezsegi szint beallitasa
     *  -2 - dicsosegtabla opcio kivalasztva
     *  -3 - kilepes kivalasztva
     *
     * */

    while (1)
    {
        int key = econio_getch(); //lenyomott gomb bekerese
        econio_flush(); //folyekonyabb kirajzolas

        if (key == KEY_UP) //felfele nyilacska lenyomasa
        {
            if (main_menu_state >= -2 && main_menu_state < 0)
            {
                main_menu_state++; //menuallas valtozo leptetese
            }
        }
        else if (key == KEY_DOWN) //lefele nyilacska lenyomasa eseten
        {
            if (main_menu_state > -2 && main_menu_state <= 0)
            {
                main_menu_state--; //menuallas valtozo leptetese
            }
        }
        else if (key == KEY_ENTER) //enter lenyomasa eseten
        {
            if (main_menu_state == 0) //jatek opcio
            {
                *global_state = 2; //jatek kezdese
                break;
            }
            if (main_menu_state == -1) //dicsosegtabla opcio
            {
                *global_state = 1; //dicsosegtabla megnyitasa
                break;
            }

            if (main_menu_state == -2) //kilepes opcio
            {
                exit(0); //kilepes a "0" hibakoddal
            }
        }

        main_menu_state_switcher(main_menu_state); //valtoztatott menu kirajzolasa

    }
}

/*menu inicializalo fuggveny*/
void main_menu_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

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