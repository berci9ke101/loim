#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

void win(int amount);
void lose(int fix_amount);
void game_init(void);
void arrow_and_reward(int questionnum, int *amount, int *fix_amount);
int diffselect(int difficulty);
int game(int difficulty);

#endif //NAGYHF_GAME_H
