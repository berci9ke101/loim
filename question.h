#ifndef NAGYHF_QUESTION_H
#define NAGYHF_QUESTION_H

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

char *load_a_random_question(void);
void free_QUESTION(QUESTION loim);
QUESTION load_question_by_difficulty(int difficulty);
void print_question(QUESTION loim);
void print_cheat(QUESTION loim);

#endif //NAGYHF_QUESTION_H