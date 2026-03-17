%{
    #include "tokens.h"
%}


%%
///variable types
"int" {return INT;}
"double" {return DOUBLE;}
"float" {return FLOAT;}
"char" {return CHAR;}
"string" {return STRING;}

///operators
"!=" {return NOT EQUAL;}
"==" {return ASSIGN;}
">=" {return GREATER THAN EQUAL;}
"<=" {return LESS THAN EQUAL;}
"&&" {return AND;}
"||" {return OR;}

"+" {return ADD;}
"-" {return SUBTRACT;}
"*" {return MULTIPLY;}
"/" {return DIVIDE;}
"%" {return MOD;}
"=" {return EQUAL;}
">" {return GREATER THAN;}
"<" {return LESS THAN;}


///keywords
"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"return" {return RETURN;}


///numbers and characters
[0-9]+ {return NUM;}
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }


///get comments
"//".* {}

"/*"        { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>.     { }
<COMMENT>\n    { }


///return nothing for whitespace
[ \t\n]+ {}


///catches extra cases
. {return yytext[0];}

%%
yywrap()