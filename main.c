#include <stdio.h>
#include "tokens.h"

extern int yylex();

int main() {
    int token;

    FILE *out = fopen("tokens.txt", "w");  // open file for writing

    if (out == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while((token = yylex())) {
        fprintf(out, "%03d ", token);  // write to file
    }

    fclose(out);  // always close the file

    return 0;
}