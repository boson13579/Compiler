%{
#include <stdio.h>
#include "Matrix.h"
#include "hw2.tab.h" 

Matrix make(char *s){
    Matrix m;
    sscanf(s, "[%d,%d]", &m.x, &m.y);
    return m;
};
int p = 0;
%}

%%

\[[0-9]+\,[ ]*[0-9]+\] {yylval.matrix = make(yytext); p+=yyleng; return MATRIX;}
\^T {p+=yyleng; return TRANSPOSE;}
"+" {yylval.opp = ++p; return ADD;}
"-" {yylval.opp = ++p; return SUB;}
"*" {yylval.opp = ++p; return MUL;}
[ ]* {p+=yyleng;}
. {p++; return yytext[0];}
\n {return 0;}

%%

