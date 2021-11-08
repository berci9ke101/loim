#include "game.h"
#include "econio.h"
#include "draw.h"
#include "scoreboard.h"
#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*aktualis kerdes jelzese, illetve a nyeremeny megadasa*/
void arrow_and_reward(int questionnum, int *amount, int *fix_amount)
{
    del_arrows();
    switch (questionnum)
    {
        case 1:
        {
            econio_gotoxy(102, 17);
            printf("->");
            *amount = 0;
            *fix_amount = 0;
            break;
        }
        case 2:
        {
            econio_gotoxy(102, 16);
            printf("->");
            *amount = 10000;
            break;
        }
        case 3:
        {
            econio_gotoxy(102, 15);
            printf("->");
            *amount = 20000;
            break;
        }
        case 4:
        {
            econio_gotoxy(102, 14);
            printf("->");
            *amount = 50000;
            break;
        }
        case 5:
        {
            econio_gotoxy(102, 13);
            printf("->");
            *amount = 100000;
            break;
        }
        case 6:
        {
            econio_gotoxy(102, 11);
            printf("->");
            *amount = 250000;
            *fix_amount = 250000;
            break;
        }
        case 7:
        {
            econio_gotoxy(102, 10);
            printf("->");
            *amount = 500000;
            break;
        }
        case 8:
        {
            econio_gotoxy(102, 9);
            printf("->");
            *amount = 750000;
            break;
        }
        case 9:
        {
            econio_gotoxy(102, 8);
            printf("->");
            *amount = 1000000;
            break;
        }
        case 10:
        {
            econio_gotoxy(102, 7);
            printf("->");
            *amount = 1500000;
            break;
        }
        case 11:
        {
            econio_gotoxy(102, 5);
            printf("->");
            *amount = 2000000;
            *fix_amount = 2000000;
            break;
        }
        case 12:
        {
            econio_gotoxy(102, 4);
            printf("->");
            *amount = 5000000;
            break;
        }
        case 13:
        {
            econio_gotoxy(102, 3);
            printf("->");
            *amount = 10000000;
            break;
        }
        case 14:
        {
            econio_gotoxy(102, 2);
            printf("->");
            *amount = 15000000;
            break;
        }
        case 15:
        {
            econio_gotoxy(102, 1);
            printf("->");
            *amount = 25000000;
            break;
        }
        case 16:
        {
            //win();
            *amount = 50000000;
            *fix_amount = 50000000;
        }
        default:
            break;
    }
}

/*jatek inicializalo fuggveny*/
void game_init(void)
{
    //kepernyo "tisztitasa"
    econio_clrscr();

#ifdef DEBUG
    console_debug(119, 25);
#endif

    //frame
    draw_rect_char_UTF8(0, 0, 119, 25, "═", "║", "╔", "╗", "╚", "╝");

    //clock
    econio_gotoxy(0, 2);
    printf("╠════════╝");
    econio_gotoxy(9, 1);
    printf("║");
    econio_gotoxy(9, 0);
    printf("╦");

    //win amount frame and text
    econio_gotoxy(96, 18);
    printf("╚═══╩═════════════════╣");
    econio_gotoxy(96, 12);
    printf("╠═══╬═════════════════╣");
    econio_gotoxy(96, 6);
    printf("╠═══╬═════════════════╣");
    econio_gotoxy(96, 0);
    printf("╦═══╦═════════════════╗");

    char amount[15][11] = {"50 000 000", "25 000 000", "15 000 000", "10 000 000", "5 000 000", "2 000 000",
                           "1 500 000", "1 000 000", "750 000", "500 000", "250 000", "100 000", "50 000", "20 000",
                           "10 000"};

    int k = 1;
    for (int i = 17; i >= 1; i--)
    {
        if (i != 6 && i != 12)
        {
            econio_gotoxy(96, i);
            printf("║%*d.║", 2, k++);
            printf("    %*s Ft", 10, amount[15 - (k - 1)]);
        }
    }

    //help
    econio_gotoxy(3, 21);
    printf("telefonos segítség (T)");
    econio_gotoxy(3, 22);
    printf("közönség véleménye (K)");


}

///*kerdesek beolvasasa nehezsegi szint szerint*/
//char *load_a_question(void)
//{
//    FILE *fp;
//    fp = fopen("../read.txt", "r");
//
//    int n = 0;
//    char *tomb;
//    char *tombuj;
//    tomb = (char *) malloc(sizeof(char));
//    do
//    {
//        n++;
//        tomb[n - 1] = fgetc(fp);
//        tombuj = (char *) malloc((n + 1) * sizeof(char));
//        for (int i = 0; i < n; i++)
//        {
//            tombuj[i] = tomb[i];
//        }
//        free(tomb);
//        tomb = tombuj;
//    } while (tomb[n - 1] != '\n');
//
//    fclose(fp);
//
//    tomb[n - 1] = '\0';
//
//    return tomb;
//}
//
//QUESTION load_question_by_difficulty(int difficulty, char *raw_text)
//{
//    QUESTION loim;
//
//    char **struct_array_type[7] = {&(loim.difficulty), &(loim.question), &(loim.A), &(loim.B), &(loim.C), &(loim.D),
//                                   &(loim.answer)};
//
//    char *copy_raw_text = raw_text;
//    for (int i = 0; i < 7; i++)
//    {
//        int n = 0;
//        do
//        {
//            n++;
//        } while (raw_text[n - 1] != ';' && raw_text[n - 1] != '\0');
//
//        *struct_array_type[i] = (char *) malloc(n * sizeof(char));
//        strncpy(*struct_array_type[i], raw_text, n);
//        (*struct_array_type[i])[n - 1] = '\0';
//
//        raw_text += n;
//    }
//
//    free(copy_raw_text);
//
//    return loim;
//}