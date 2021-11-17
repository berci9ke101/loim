#include "question.h"
#include "econio.h"
#include "functions.h"
#include "draw.h"
#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

#define FILENAME "../loim.csv"

/*osszes kerdes betoltese*/
char **load_questions(void)
{
    /*jelenlegi sor sorszama es a fajl max sorszamanak megadasa*/
    int linenum = 0;
    int maxlinecount = count_lines(FILENAME);

    /*fajl megnyitasa*/
    FILE *fp;
    fp = fopen(FILENAME, "r");

    char **questions = (char **) malloc((maxlinecount - 1) * sizeof(char *));

    /*hibakezeles*/
    if (!questions)
    {
        econio_clrscr();
        perror("Nem sikerült memoriát foglalni a kérdéseknek!");
        exit(-3);
    }

    if (fp)
    {
        do
        {
            int index = 0;
            char *string;
            char *newstring;
            string = (char *) malloc(sizeof(char));

            /*hibakezeles*/
            if (!string)
            {
                free(questions);
                econio_clrscr();
                perror("Nem sikerült memoriát foglalni az egyik kérdésnek!");
                exit(-3);
            }
            do
            {
                index++;
                string[index - 1] = fgetc(fp);
                newstring = (char *) malloc((index + 1) * sizeof(char));

                /*hibakezeles*/
                if (!newstring)
                {
                    free(questions);
                    free(string);
                    econio_clrscr();
                    perror("Nem sikerült memoriát foglalni a kérdés egyik mezejének!");
                    exit(-3);
                }

                for (int i = 0; i < index; i++)
                {
                    newstring[i] = string[i];
                }
                free(string);
                string = newstring;
            } while (string[index - 1] != '\n');

            string[index - 1] = '\0';

            questions[linenum] = string;

            linenum++;
        } while (linenum != (maxlinecount - 1));
    }
    else
    {
        econio_clrscr();
        perror("Kérdések fájl hiányzik."); //hiba eseten kilepes adott hibakoddal
        exit(-4);
    }

    fclose(fp);

    return questions;

}

/*random kerdes betoltese */
char *load_a_random_question(char **questions)
{
    int maxline = count_lines(FILENAME);
    int randomnum = rand() % (maxline + 1);

    return questions[randomnum];
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

/*kerdesek tomb felszabaditasa*/
void freeup_questions_array(char **questions)
{
    int max = (count_lines(FILENAME) - 1);
    for (int i = 0; i < max; i++)
    {
        free(questions[i]);
    }

    free(questions);
}

/*kerdes betoltese nehezseg szerint*/
QUESTION load_question_by_difficulty(int difficulty, char **questions)
{
    QUESTION loim = {"0", "0", "0", "0", "0", "0", "0"};

    char **struct_array_type[7] = {&(loim.difficulty), &(loim.question), &(loim.A), &(loim.B), &(loim.C), &(loim.D),
                                   &(loim.answer)};

    char str_difficulty[3];
    sprintf(str_difficulty, "%d", difficulty);

    while (strcmp(str_difficulty, loim.difficulty) != 0)
    {
        char *raw_text = load_a_random_question(questions);
        for (int i = 0; i < 7; i++)
        {
            int n = 0;
            do
            {
                n++;
            } while (raw_text[n - 1] != ';' && raw_text[n - 1] != '\0');

            *struct_array_type[i] = (char *) malloc(n * sizeof(char));

            /*hibakezeles*/
            if (!struct_array_type[i])
            {
                for (int k = 0; k <= i; k++)
                {
                    free(struct_array_type[i]);

                }
                freeup_questions_array(questions);
                econio_clrscr();
                perror("Nem sikerült memoriát foglalni a kérdés egyik mezejének!");
                exit(-3);
            }
            strncpy(*struct_array_type[i], raw_text, n);
            (*struct_array_type[i])[n - 1] = '\0';

            raw_text += n;
        }

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
    int length = strlen(string);
    if (length < 69)
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


    /*QUESTION*/
    for (int i = 0; i < 8; i++)
    {
        econio_gotoxy(16, (4 + i));
        for (int k = 0; k < 70; k++)
        {
            printf(" ");
        }
    }

    econio_gotoxy(16, 4);
    int index = 0;
    bool used = false;
    char *string = cut(loim.question);
    int shift_line = 1;
    do
    {
        if (string[index] == '\n')
        {
            econio_gotoxy(16, (4 + shift_line));
            index++;
            printf("%c", string[index]);
            shift_line++;
            used = true;
        }
        else
        {
            if (!used)
            {
                printf("%c", string[index]);
            }
            used = false;
            index++;
        }

    } while (string[index] != '\0');
}

/*helyes valasz betujelenek kirajzolasa*/
void print_cheat(QUESTION loim)
{
    /*3x3as mezo kitisztitasa*/
    for (int i = 3; i < 6; i++)
    {
        econio_gotoxy(3, i);
        printf("   ");
    }

    /*helyes megfejtes kiirasa*/
    econio_gotoxy(4, 4);
    printf("%s", loim.answer);
}