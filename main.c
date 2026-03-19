#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "tokens.h"

extern int yylex();
extern FILE *yyin;

int main(int argc, char *argv[]) {
    int token;

    if (argc != 2) {
        printf("Usage: %s <input_directory>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    FILE *out = fopen("tokens.txt", "w");
    if (out == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        // skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name);

        FILE *in = fopen(filepath, "r");
        if (in == NULL)
            continue;

        yyin = in;
        yyrestart(in);  // reset lexer for new file

        // print filename on its own line
        fprintf(out, "%s\n", entry->d_name);

        // print tokens on next line
        while((token = yylex())) {
            fprintf(out, "%03d ", token);
        }

        fprintf(out, "\n");  // blank line between files

        fclose(in);
    }

    closedir(dir);
    fclose(out);

    return 0;
}