%{
#include <stdio.h>
#include <string.h>

int now = 0;

%}

email \w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*\n
string1 \"[^\"]*\"\n
string2 \'[^\']*\'\n
integer [0-9]+\n
float1 [0-9]+\.[0-9]*\n
float2 [0-9]*\.[0-9]+\n
variable [a-zA-Z_][a-zA-Z0-9_]*\n


%x comment
%%

{integer} { if(now != )printf("%.*s INTERGER\n", yyleng-1, yytext);}
{float1} { printf("%.*s FLOAT\n", yyleng-1, yytext);}
{float2} { printf("%.*s FLOAT\n", yyleng-1, yytext);}
{string1} { printf("%.*s STRING\n", yyleng-1, yytext);}
{string2} { printf("%.*s STRING\n", yyleng-1, yytext);}
{email} { printf("%.*s EMAIL\n", yyleng-1, yytext);}
{variable} { printf("%.*s VARIABLE\n", yyleng-1, yytext);}

.*\n {}
.* {}
%%

int main() {
    yylex();
    return 0;
}