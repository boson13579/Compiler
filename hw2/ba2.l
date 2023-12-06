%{
#include <stdbool.h>
#include <stdio.h>
int i = 0;
%}

name [A-Z]+", "[A-Z][a-z]+"-"[A-Z][a-z]+
email [0-9]+"@"[a-z]+\.([a-z]+\.[a-z]+|[a-z]+)
datebig ([0-9]{4})\/((01)|(03)|(05)|(07)|(08)|(10)|(12))\/(0[1-9]|[1-2][0-9]|3[0-1])
datesmall ([0-9]{4})\/((04)|(06)|(09)|(11))\/(0[1-9]|[1-2][0-9]|30)
datefeb ([0-9]{4})\/02\/(0[1-9]|[1-2][0-9])
ISBN "978-"[0-9]-[0-9]{6}-[0-9]{2}-[0-9]
bookname [A-Z][a-z]+(_[A-Z][a-z]+)*
%%

{bookname} {if (i!=1){
    printf("Book name:%s\n", yytext);
    i=1;
}}
{name} {
    if (i!=2){
        printf("Author:%s\n", yytext);
        i=2;
    }
}
{datebig} {
    if (i!=3){
        printf("Publication date:%s\n", yytext);
        i=3;
    }
}
{datesmall} {
    if (i!=3){
        printf("Publication date:%s\n", yytext);
        i=3;
    }
}
{datefeb} {
    if (i!=3){
        printf("Publication date:%s\n", yytext);
        i=3;
    }
}
{ISBN} {if (i!=4){
    printf("ISBN:%s\n", yytext);
    i=4;
}}
\n {}
. {}
%%
int main() {
    yylex();
    return 0;
}
