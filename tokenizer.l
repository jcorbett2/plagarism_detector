%{
#include "tokens.h"
%}

%option noyywrap
%x COMMENT

%%


"int" {return INT;}
"double" {return DOUBLE;}
"float" {return FLOAT;}
"char" {return CHAR;}
"string" {return STRING;}


"!=" {return NEQ;}
"==" {return EQ;}
">=" {return GTE;}
"<=" {return LTE;}
"&&" {return AND;}
"||" {return OR;}


"+" {return ADD;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return ASSIGN;}
">" {return GT;}
"<" {return LT;}


"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"if" {return IF;}
"else" {return ELSE;}
"return" {return RETURN;}


[0-9]+ {return NUM;}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}


"//".* {}

"/*"        { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>.     { }
<COMMENT>\n    { }


[ \t\n]+ {}


. {return yytext[0];}

%%
