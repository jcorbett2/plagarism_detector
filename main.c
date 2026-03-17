#include <stdio.h>
#include "tokens.h"

extern int yylex();
extern char *yytext;

int main()
{
    int token;

    while((token = yylex()))
    {
        printf("Token: %d\n", token);
    }

    return 0;
}