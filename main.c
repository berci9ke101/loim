#include <stdio.h>
#include "functions.h"
#include "menu.h"

int main()
{
    //ablak nevenek, kodolasanak es meretenek beallitasa
    init_console_window();

#ifdef DEBUG
    debug_console(119, 25);
#endif

    //MAIN MENU
    init_main_menu();
    main_menu_buttons();

    return 0;
}

