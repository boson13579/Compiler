%{
#include "hw1.tab.h"
%}

%%

(p|P) {return(Permutaion);}
(c|C) {return(Combination);}
[0-9]+ {yylval.ival = atoi(yytext); return(INUMBER);}
(\+|\-) {return(yytext[0]);}
\n {;}
\t {;}
. {;}

%%