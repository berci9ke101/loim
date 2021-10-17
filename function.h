//
// Function source file
//
#include <windows.h>
#include <conio.h>


/*sorok megszamolasa egy fajlban*/
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

/*fajl kiiratasa a konzolba*/
void print_to_console(char *file_name)
{
    //fajl betoltese
    FILE *file;
    file = fopen(file_name, "r");
    char buffer[255];

    //jelenlegi sor es a max sorszam valtozoi
    int linenum = 1;
    int max_line_count = count_lines(file_name);

    //kiiras
    if (file)
    {
        while (linenum <= max_line_count)
        {
            fgets(buffer, 255, file);
            printf("%s", buffer);
            linenum++;
        }
        fclose(file);
    }
    else
    {
        perror("");
    }
}

/*konzolablak elnevezese es meretenek megvaltoztatasa*/
void init_console_window(void)
{
    system("mode con:cols=120 lines=25");
    system("title Legyel Te Is Adocsalo");
}

/*karakter olvasasa portolas miatt*/
char char_read(void)
{
    return getch();
}