#include "question.h"
#include "econio.h"
#include "functions.h"
#include "draw.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>

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

    int index = 0;
    char *string;
    char *newstring;
    string = (char *) malloc(sizeof(char));
    do
    {
        index++;
        string[index - 1] = fgetc(fp);
        newstring = (char *) malloc((index + 1) * sizeof(char));
        for (int i = 0; i < index; i++)
        {
            newstring[i] = string[i];
        }
        free(string);
        string = newstring;
    } while (string[index - 1] != '\n' && string[index - 1] != EOF);

    string[index - 1] = '\0';


    fclose(fp);

    return string;
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

/*kerdes felvagdosasa 70es (vagy kisebb) blokkokba es ezek elvalasztasa '\n'- nel*/
char *cut(char *string)
{
    int size = strlen(string);
    if (size < 69)
    {
        return string;
    }
    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (i % 69 == 0 && i > 0)
        {
            if (string[i] == ' ')
            {
                string[i] = '\n';
            }
            else
            {
                int j = i;
                while (string[j] != ' ')
                {
                    --j;
                }
                string[j] = '\n';
            }
        }
    }
    return string;
}

/*kerdes es a valaszok kirajzolasa*/
void print_question(QUESTION loim)
{
    /*A*/
    del_question("A");
    econio_gotoxy(17, 12);
    printf("A: %s", loim.A);

    /*B*/
    del_question("B");
    econio_gotoxy(17, 13);
    printf("B: %s", loim.B);

    /*C*/
    del_question("C");
    econio_gotoxy(52, 12);
    printf("C: %s", loim.C);

    /*D*/
    del_question("D");
    econio_gotoxy(52, 13);
    printf("D: %s", loim.D);

//    /*QUESTION*/
//    econio_gotoxy(1, 19);
//    printf("                                                                                                                     ");
//    econio_gotoxy(1, 19);
//    printf("%s", loim.question);

    /*QUESTION*/
    for (int i = 0; i < 8; i++)
    {
        econio_gotoxy(16, (4 + i));
        for (int k = 0; k < 70; k++)
        {
            printf(" ");
        }
    }

//    char *p = cut(loim.question);
//    int t = 0;
//    int next_line = 0;
//    while (*p + t != '\0')
//    {
//        printf("%c", p[t]);
//        t++;
//    }

    char *p = loim.question;
    for (int i = 0; i < ((strlen(loim.question) / 69) + 1); i++)
    {
        econio_gotoxy(16, (4 + i));
        printf("%-.*s", 69, p);
        p += 69;
    }
}

void print_cheat(QUESTION loim)
{
    econio_gotoxy(4, 4);
    printf("%s", loim.answer);
}