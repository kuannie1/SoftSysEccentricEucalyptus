%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char *msg);
%}

%union {
  float f;
}

%token <f> NUM
%type <f> A B E H T D F

%%

S : F           {printf("%f\n", $1);}
  ;

A : '(' '+'     {$$ = 0;}
  | A F         {$$ = $1 + $2;}
  ;

E : '(' '-'     {$$ = 0;}
  ;

H : E F         {$$ = $2;}
  ;

B : H F         {$$ = $1 - $2;}
  | B F         {$$ = $1 - $2;}
  ;

T : '(' '*'     {$$ = 1;}
  | T F         {$$ = $1 * $2;}
  ;

D : '(' '/'     {$$ = 1;}
  | D F         {$$ = $1 / $2;}
  ;

F : NUM         {$$ = $1;}
  | A ')'       {$$ = $1;}
  | B ')'       {$$ = $1;}
  | T ')'       {$$ = $1;}
  | D ')'       {$$ = $1;}
  | H ')'       {$$ = -$1;}
  | '-' F       {$$ = -$2;}
  ;


%%

void yyerror(char *msg){
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main() {
  yyparse();
  return 0;
}
