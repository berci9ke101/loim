#include "question.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

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

int count_lines(char *file_name)
{
    //fajl megnyitasa
    FILE *file;
    file = fopen(file_name, "r");
    char c;
    int max_line_count = 1;

    //karakter beolvasas a fajl vege karakterig
    while (c != EOF)
    {
        c = getc(file);
        if (c == '\n')
        {
            max_line_count++;
        }
    }
    fclose(file);

    //visszateres a sorok szamaval
    return max_line_count;
}

/*veletlenszeru kerdesbetoltese*/
char *load_a_random_question(void)
{
    /*jelenlegi sor sorszama es a fajl max sorszamanak megadasa*/
    int linenum = 0;
    int maxlinecount = count_lines("../loim.csv");

    /*veletlenszeru sor sorszama*/
    int randomline = (rand() % (maxlinecount + 1) + 1);

    /*fajl megnyitasa*/
    FILE *fp;
    fp = fopen("../loim.csv", "r");

    /*mozgas a fajlban*/
    while (linenum != randomline)
    {
        char c = fgetc(fp);
        if (c == '\n')
        {
            linenum++;
        }
    }

    int n = 0;
    char *tomb;
    char *tombuj;
    tomb = (char *) malloc(sizeof(char));
    do
    {
        n++;
        tomb[n - 1] = fgetc(fp);
        tombuj = (char *) malloc((n + 1) * sizeof(char));
        for (int i = 0; i < n; i++)
        {
            tombuj[i] = tomb[i];
        }
        free(tomb);
        tomb = tombuj;
    } while (tomb[n - 1] != '\n' && tomb[n - 1] != EOF);

    tomb[n - 1] = '\0';


    fclose(fp);

    return tomb;
}

/*lefoglalt kerdes felszabaditasa*/
void free_QUESTION(QUESTION loim)
{
    free(loim.difficulty);
    free(loim.question);
    free(loim.A);
    free(loim.B);
    free(loim.C);
    free(loim.D);
    free(loim.answer);
}

/*kerdes betoltese nehezseg szerint*/
QUESTION load_question_by_difficulty(int difficulty)
{
    QUESTION loim = {"0", "0", "0", "0", "0", "0", "0"};

    char **struct_array_type[7] = {&(loim.difficulty), &(loim.question), &(loim.A), &(loim.B), &(loim.C), &(loim.D),
                                   &(loim.answer)};

    char str_difficulty[3];
    sprintf(str_difficulty, "%d", difficulty);

    while (strcmp(str_difficulty, loim.difficulty) != 0)
    {
        char *raw_text = load_a_random_question();
        char *copy_raw_text = raw_text;
        for (int i = 0; i < 7; i++)
        {
            int n = 0;
            do
            {
                n++;
            } while (raw_text[n - 1] != ';' && raw_text[n - 1] != '\0');

            *struct_array_type[i] = (char *) malloc(n * sizeof(char));
            strncpy(*struct_array_type[i], raw_text, n);
            (*struct_array_type[i])[n - 1] = '\0';

            raw_text += n;
        }

        free(copy_raw_text);
        if (strcmp(str_difficulty, loim.difficulty) != 0)
        {
            free_QUESTION(loim);
        }
    }

    return loim;
}