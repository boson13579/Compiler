%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void yyerror(char *s);
int arr[1000], p = -1;
%}

%union {
    char* str;
    int ival;
}


%token <ival> INUMBER
%token add sub mul mod inc dec load 

%%

abc : abc expr
    ;

expr : load INUMBER {arr[++p] = $2;}
     | add { if (p >= 1) arr[p-1] = arr[p] + arr[p-1]; else yyerror("Invalid format"); p--; }
     | sub { if (p >= 1) arr[p-1] = arr[p] - arr[p-1]; else yyerror("Invalid format"); p--; }
     | mul { if (p >= 1) arr[p-1] = arr[p] * arr[p-1]; else yyerror("Invalid format"); p--; }
     | mod { if (p >= 1) arr[p-1] = arr[p] % arr[p-1]; else yyerror("Invalid format"); p--; }
     | inc { if (p >= 0) arr[p] = arr[p] + 1; else yyerror("Invalid format");}
     | dec { if (p >= 0) arr[p] = arr[p] - 1; else yyerror("Invalid format");}
     ;

%%
void yyerror(char *s) {
    printf("%s\n", s);
    exit(0);
}

int main() {
    yyparse();
    if (p == 0)
        printf("%d", arr[0]);
    else
        yyerror("Invalid format");
    return 0;
}

