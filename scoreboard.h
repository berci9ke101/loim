#ifndef NAGYHF_SCOREBOARD_H
#define NAGYHF_SCOREBOARD_H

typedef struct SCOREBOARD
{
    char name[20 + 1];
    int hour;
    int minute;
    int second;
    char winamount[10 + 1];
} SCOREBOARD;

void scoreboard_print_to_console(void);

void scoreboard_init(void);

void scoreboard_buttons(int *global_state);

void read_sort_write(void);

void write_to_scoreboard(char *string);

#endif //NAGYHF_SCOREBOARD_H
