%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int stack[1000];
int top = -1;
void push(int val){
        stack[++top] = val;
}
int pop (){
    if (top = -1)
        return 0;
    return stack[top--];
}

void yyerror(char *s);
void p(bool i);
void ror();
void reand();

%}

%union {
    bool ibool;
}

%type <ibool> abc
%type <ibool> exprs
%type <ibool> expr
%token AND EAND OR EOR NOT ENOT TRUE FALSE

%%

abc : expr {int tmp = pop(); p(tmp == 2 ? true : false);}

expr : AND exprs EAND {reand();}
     | OR exprs EOR {ror();}
     | NOT expr ENOT {int tmp = pop(); push(tmp == 2 ? 1 : 2);}
     | TRUE {push(2);}
     | FALSE {push(1);}
     ;
exprs : exprs expr 
      | 
      ;

%%
void p(bool i){
    if(i)
        printf("true\n");
    else
        printf("false\n");
}

void ror(){
    bool ret = false;
    int tmp;
    while(tmp = pop()){
        ret |= tmp == 2 ? true : false;
    }
    push(ret ? 2 : 1);
}

void reand(){
    bool ret = true;
    int tmp;
    while(tmp = pop()){
        ret &= tmp == 2 ? true : false;
    }
    push(ret ? 2 : 1);
}

void yyerror(char *s) {
    printf("Syntax Error\n");
    exit(0);
}

int main() {
    yyparse();
    return 0;
}