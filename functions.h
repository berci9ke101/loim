
#ifndef NAGYHF_FUNCTIONS_H
#define NAGYHF_FUNCTIONS_H

int count_lines(char *file_name);
void print_to_console(char *file_name);
void init_console_window(void);
char char_read(void);
void buttons(void);
void draw_rect_char_UTF8(int x, int y, int width, int height, char *hor, char *vert, char *t_left, char *t_right, char *b_left, char *b_right);
void init_main_menu(void);

#endif //NAGYHF_FUNCTIONS_H
