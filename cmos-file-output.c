#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "tokens.h"

extern int yylex();
extern FILE *yyin;

int main(int argc, char *argv[]) {
    ///stores token from lex program
    int token;

    ///checks to make sure input is only .exe and directory name
    if (argc != 2) 
    {
        printf("Usage: %s <input_directory>\n", argv[0]);
        return 1;
    }

    ///store directory and open it
    DIR *dir = opendir(argv[1]);
    if (dir == NULL)///errror if directory does not exist
    {
        printf("Error: directory not found\n");
        return 1;
    }


    ///create output file to send tokenized data
    FILE *out = fopen("tokens.txt", "w");
    if (out == NULL)///error if cannot open
    {
        printf("Error: cannot open file\n");
        return 1;
    }

    ///read each file in the directory one by one
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {

        ///skip current and parent directory to only process necessary files
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        ///combine filepath into full name to access it
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name);

        ///access file from path found
        FILE *in = fopen(filepath, "r");
        if (in == NULL)///skip if no file is opened
            continue;

        ///reads file
        yyin = in;
        yyrestart(in);///reset lexer state

        ///print filename on its own line
        fprintf(out, "%s\n", entry->d_name);

        ///print tokens on next line
        while((token = yylex())) {
            fprintf(out, "%03d ", token);
        }

        fprintf(out, "\n");///move to next line for next file

        fclose(in);
    }

    closedir(dir);
    fclose(out);

    return 0;
}