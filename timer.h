#include <time.h>

#ifndef NAGYHF_TIMER_H
#define NAGYHF_TIMER_H

time_t timer(time_t prev_time, int *hour, int *minute, int *second);
void print_time(int hour, int minute, int second);

#endif //NAGYHF_TIMER_H
