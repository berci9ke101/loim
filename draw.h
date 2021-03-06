#ifndef NAGYHF_DRAW_H
#define NAGYHF_DRAW_H
#include "question.h"

char *percent_block(int number);
void del_audience(void);
void half(QUESTION loim);
void del_answer(char *ABCD);
void draw_audience(char *answer);
void del_arrows(void);
int vert_align(int window_width, int rectangle_width);
int hor_align(int window_height, int rectangle_height);
void draw_rect_char_UTF8(int x, int y, int width, int height, char *hor, char *vert, char *t_left, char *t_right,
                         char *b_left, char *b_right);

#endif //NAGYHF_DRAW_H
