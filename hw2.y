%{
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
Matrix Transpose(Matrix m);
Matrix checkAdd(Matrix m1, Matrix m2, int p);
Matrix checkSub(Matrix m1, Matrix m2, int p);
Matrix checkMul(Matrix m1, Matrix m2, int p);
void yyerror(char *s);
%}

%union {
    Matrix matrix;
    int opp;
}

%type <matrix> expr
%token <matrix> MATRIX
%token <opp> ADD SUB MUL
%token TRANSPOSE

%left ADD SUB 
%left MUL
%nonassoc TRANSPOSE 

%%

expr : expr ADD expr   { $$ = checkAdd($1, $3, $2); }
     | expr SUB expr   { $$ = checkSub($1, $3, $2); }
     | expr MUL expr   { $$ = checkMul($1, $3, $2); }
     | expr TRANSPOSE { $$ = Transpose($1); }
     | '(' expr ')'    { $$ = $2; }
     | MATRIX          { $$ = $1; }
     ;
%%

Matrix Transpose(Matrix m) {
    Matrix result;
    result.x = m.y;
    result.y = m.x;
    return result;
}

Matrix checkAdd(Matrix m1, Matrix m2, int p) {
    Matrix result;
    if (m1.x == m2.x && m1.y == m2.y) {
        result.x = m1.x;
        result.y = m1.y;
    } else {
        printf("Semantic error on col %d", p);
        exit(0);
    }
    return result;
}

Matrix checkSub(Matrix m1, Matrix m2, int p) {
    Matrix result;
    if (m1.x == m2.x && m1.y == m2.y) {
        result.x = m1.x;
        result.y = m1.y;
    } else {
        printf("Semantic error on col %d", p);
        exit(0);
    }
    return result;
}

Matrix checkMul(Matrix m1, Matrix m2,int p) {
    Matrix result;
    if (m1.y == m2.x) {
        result.x = m1.x;
        result.y = m2.y;
    } else {
        printf("Semantic error on col %d", p);
        exit(0);
    }
    return result;
}

void yyerror(char *s) {
    printf("Syntax Error\n");
    exit(0);
}

int main() {
    yyparse();
    printf("Accepted\n");
    return 0;
}