#ifndef NAGYHF_FUNCTIONS_H
#define NAGYHF_FUNCTIONS_H

void bubble_sort(int size, int *array);
void hidecursor(void);
int count_lines(char *file_name);
void console_init(void);
void console_debug(int width, int height);
int calc_win_amount_length(int win_amount);
void split_num(int number);
char *split_up_num(int number);
void reverse_string(char *string);

#endif //NAGYHF_FUNCTIONS_H
