#include <stdio.h>
#include <stdbool.h>
#include "function.h"

int main()
{
    bool exit = false;

    init_console_window();
    print_to_console("../UI/MAIN_MENU.txt");

    while (!exit)
    {
        switch (char_read())
        {
            case '1':
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
    return 0;
}
