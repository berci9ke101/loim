#ifndef NAGYHF_SCOREBOARD_H
#define NAGYHF_SCOREBOARD_H

void scoreboard_right_align(char *text, int max_length);
void scoreboard_print_to_console(void);
void scoreboard_init(void);
void scoreboard_buttons(int *global_state);

#endif //NAGYHF_SCOREBOARD_H
