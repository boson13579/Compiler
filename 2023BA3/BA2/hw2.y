%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//function define in here but should declare in the bottom

void yyerror(char *s);
void p(bool i);

//stuct should using with typedef
//typedef struct {}haha;
typedef struct {
    bool arr[15];
    int i;
}len; 

len clen();
bool ror(len a);
bool reand(len a);
len lstep(len now, bool a);

%}

%union {
    bool ibool;
    len exps;
}

%type <ibool> abc
%type <exps> exprs
%type <ibool> expr
%token AND EAND OR EOR NOT ENOT TRUE FALSE

%%

abc : expr {p($1);}

expr : AND exprs EAND{$$ = reand($2);}
     | OR exprs EOR {$$ = ror($2);}
     | NOT expr ENOT {$$ = !$2;}
     | TRUE {$$ = true;}
     | FALSE {$$ = false;}
     ;
exprs : exprs expr {$$ = lstep($1, $2);}
      | {$$ = clen();}
      ;

%%
void p(bool i){
    if(i)
        printf("true\n");
    else
        printf("false\n");
}

len clen(){
    len ret;
    ret.i = 0;
    return ret;
}

bool ror(len a){
    if(a.i == 0)
        return false;
    bool ret = false;
    for(int i=a.i-1; i>=0 ; i--)
        ret |= a.arr[i];
    return ret;
}

bool reand(len a){
    if (a.i == 0)
        return true;
    bool ret = true;
    for(int i=a.i-1; i>=0 ; i--)
        ret &= a.arr[i];
    return ret;
}

len lstep(len now, bool a){
    now.arr[now.i++] = a;
    return now;
}

void yyerror(char *s) {
    printf("Syntax Error\n");
    exit(0);
}

int main() {
    yyparse();
    return 0;
}