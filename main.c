#include "functions.h"
#include "main_menu.h"

int main()
{
    //ablak nevenek, kodolasanak es meretenek beallitasa
    console_init();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //MAIN MENU
    main_menu_init();
    main_menu_buttons();

    while (1 == 1)
    {
        ;
    }

    return 0;
}

