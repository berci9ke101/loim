#ifndef NAGYHF_SCOREBOARD_H
#define NAGYHF_SCOREBOARD_H

void scoreboard_print_to_console(void);
void scoreboard_init(void);
void scoreboard_buttons(int *global_state);

void write_to_scoreboard(char *string);

#endif //NAGYHF_SCOREBOARD_H
