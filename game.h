#ifndef NAGYHF_GAME_H
#define NAGYHF_GAME_H

/*KERDES STRUKTURA*/
typedef struct QUESTION
{
    char *difficulty;
    char *question;
    char *A;
    char *B;
    char *C;
    char *D;
    char *answer;
} QUESTION;

char *load_a_question(void);
QUESTION load_question_by_difficulty(int difficulty, char *raw_text);
void game_init(void);
void arrow_and_reward(int questionnum, int *amount, int *fix_amount);

#endif //NAGYHF_GAME_H
