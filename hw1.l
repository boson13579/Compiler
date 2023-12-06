%{
#include "hw1.tab.h"
%}

%%

\n {;}
\t {;}
"load " {return(load);}
"add" {return(add);}
"sub" {return(sub);}
"mul" {return(mul);}
"mod" {return(mod);}
"inc" {return(inc);}
"dec" {return(dec);}
[0-9]+ {yylval.ival = atoi(yytext); return(INUMBER);}
. {;}

%%