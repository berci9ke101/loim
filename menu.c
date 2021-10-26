#include "econio.h"
#include "draw.h"

void main_menu_state_switcher(int menu_state)
{
    if (menu_state == 0)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');

    }
    else if (menu_state == -1)
    {
        econio_gotoxy((vert_align(119, 17) + 1), 10);
        printf("%c", ' ');
        econio_gotoxy((vert_align(119, 17) + 1), 12);
        printf("%c", 'X');
        econio_gotoxy((vert_align(119, 11) + 1), 14);
        printf("%c", ' ');
    }
    else if (menu_state == -2)
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
    int menu_state = 0;
    while (1)
    {
        int key = econio_getch();
        econio_flush();

        if (key == KEY_UP)
        {
            if (menu_state >= -2 && menu_state < 0)
            {
                menu_state++;
            }
        }
        else if (key == KEY_DOWN)
        {
            if (menu_state > -2 && menu_state <= 0)
            {
                menu_state--;
            }
        }
        else if (key == KEY_ENTER)
        {
            if (menu_state == -2)
            {
                break;
            }
        }

        main_menu_state_switcher(menu_state);

    }
}