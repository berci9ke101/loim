#include "timer.h"
#include <stdio.h>
#include "econio.h"
#include <time.h>

time_t timer(time_t prev_time, int *hour, int *minute, int *second)
{
    time_t current_time = time(0);

    int delta = current_time - prev_time;

    *second += delta;

    if (*second == 60)
    {
        *second = 0;
        (*minute)++;
    }

    if (*minute == 60)
    {
        *minute = 0;
        (*hour)++;
    }

    return current_time;

}

void print_time(int hour, int minute, int second)
{
    econio_gotoxy(1, 1);
    printf("%02d:%02d:%02d", hour, minute, second);
}