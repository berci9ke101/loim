#ifndef NAGYHF_DRAW_H
#define NAGYHF_DRAW_H

int vert_align(int window_width, int rectangle_width);
int hor_align(int window_height, int rectangle_height);
void draw_rect_char_UTF8(int x, int y, int width, int height, char *hor, char *vert, char *t_left, char *t_right,
                         char *b_left, char *b_right);
void text_left_align(char *text, int max_length);

#endif //NAGYHF_DRAW_H
