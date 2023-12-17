%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void yyerror(char *s);
int power(int a){
    int ret = 1;
    for(int i=2; i<=a ; ++i)
        ret *= i;
    return ret;
}
int p(int n, int k){
    return power(n)/power(n-k);
}
int c(int n, int m){
    return power(n)/(power(m)*power(n-m));
}
%}

%union {
    char* str;
    int ival;
}

%type <ival> expr abc 
%token <ival> INUMBER
%token Permutaion Combination
%left '+' '-'  

%%

abc : abc expr {printf("%d\n", $2);}
    |
    ;

expr : expr '+' expr {$$ = $1 + $3;}
     | expr '-' expr {$$ = $1 - $3;}
     | Permutaion INUMBER INUMBER {$$ = p($2, $3);}
     | Combination INUMBER INUMBER {$$ = c($2, $3);}
%%
void yyerror(char *s) {
    printf("Wrong Formula");
    /* exit(0); */
}

int main() {
    yyparse();
    
    return 0;
}

