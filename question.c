#include "question.h"
#include "econio.h"
#include "functions.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>

///*kerdes string feldarabolasa 70-es ,ujsorral elvalasztott, karakterblokkokba*/
//char *cut_up_string(char *string)
//{
//    int size = strlen(string);
//    int loc = 0;
//    int iter = ((size / 70) + 1);
//    for (int i = 0; i < size; i++)
//    {
//        for (int k = 1; k <= iter; k++)
//        {
//            while (i != (70 * k))
//            {
//                if (string[i] == ' ')
//                {
//                    string[i] = '\n';
//                }
//                else
//                {
//                    int j=i;
//                    while (string[j] != ' ')
//                    {
//                        j--;
//                    }
//                    i=j;
//                }
//
//            }
//        }
//    }
//    string[size - 1] = '\0';
//    return string;
//}

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

/*kerdes es a valaszok kirajzolasa*/
void print_question(QUESTION loim)
{
    /*A*/
    econio_gotoxy(16, 12);
    printf("                                        ");
    econio_gotoxy(16, 12);
    printf("A: %s", loim.A);

    /*B*/
    econio_gotoxy(16, 13);
    printf("                                        ");
    econio_gotoxy(16, 13);
    printf("B: %s", loim.B);

    /*C*/
    econio_gotoxy(59, 12);
    printf("                                        ");
    econio_gotoxy(59, 12);
    printf("C: %s", loim.C);

    /*D*/
    econio_gotoxy(59, 13);
    printf("                                        ");
    econio_gotoxy(59, 13);
    printf("D: %s", loim.D);

    /*QUESTION*/
    econio_gotoxy(1, 19);
    printf("                                                                                                                     ");
    econio_gotoxy(1, 19);
    printf("%s", loim.question);
}

void print_cheat(QUESTION loim)
{
    econio_gotoxy(4,4);
    printf("%s", loim.answer);
}