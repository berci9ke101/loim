#include <stdio.h>
#include <windows.h>
#include "econio.h"
#include "functions.h"
#include "draw.h"

/*kurzor elrejtese*/
/*kozbeszerezve*/
void hidecursor(void)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
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
    system("mode con:cols=119 lines=25");
    econio_set_title("LOIM");
    SetConsoleOutputCP(CP_UTF8);
    hidecursor();
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

/*ez a fuggveny szimulalja az f gomb lenyomasat*/
void pressF(void)
{
    //'f' key down
    keybd_event(0x46,0x45,KEYEVENTF_EXTENDEDKEY|0,0);
    //'f' key up
    keybd_event(0x46,0x45,KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP,0);
}

/*tisztogato fuggveny*/
/*void clean_master_pro_900(void **p)
{

}*/