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
"bool" {return BOOL;}
"long" {return LONG;}
"short" {return SHORT;}
"unsigned" {return UNSIGN;}
"signed" {return SIGN;}
"void" {return VOID;}
"const" {return CONST;}
"static" {return STATIC;}
"new" {return NEW;}
"delete" {return DELETE;}



"==" {return EQ;}
">=" {return GTE;}
"<=" {return LTE;}
"&&" {return AND;}
"||" {return OR;}
"++" {return INC;}
"--" {return DEC;}
"+=" {return ADD_TO;}
"-=" {return SUB_FROM;}
"*=" {return MULT_BY;}
"/=" {return DIV_BY;}
"->" {return ARROW;}
"::" {return SCOPE;}

"+" {return ADD;}
"-" {return SUB;}
"*" {return MULT;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return ASSIGN;}
">" {return GT;}
"<" {return LT;}
"&" {return REF;}
"!" {return NOT;}




"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"if" {return IF;}
"else" {return ELSE;}
"return" {return RETURN;}
"switch" {return SWITCH;}
"case" {return CASE;}
"break" {return BREAK;}
"continue" {return CONT;}

"class" {return CLASS;}
"struct" {return STRUCT;}
"public" {return PUB;}
"private" {return PRIV;}

"true" {return TRUE;}
"false" {return FALSE;}
"nullptr" {return NULL;}
"NULL" {return NULL;}



"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"[" { return LBRACKET; }
"]" { return RBRACKET; }
";" { return SEMICOLON; }
"," { return COMMA; }
"." { return DOT; }


[0-9]+"."[0-9]+ {return NUM;}
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
