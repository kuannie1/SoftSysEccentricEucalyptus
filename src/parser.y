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

S : F           {printf("%f\n", $1);} // Print out final value
  ;

A : '(' '+'     {$$ = 0;} // Initialize A token with value 0
  | A F         {$$ = $1 + $2;} // Subsequent F tokens are added to A token
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

F : NUM         {$$ = $1;} // All NUM's become F token
  | A ')'       {$$ = $1;} // Reduce A token to F once parenthesis close
  | B ')'       {$$ = $1;}
  | T ')'       {$$ = $1;}
  | D ')'       {$$ = $1;}
  | H ')'       {$$ = -$1;}
  | '-' F       {$$ = -$2;} // Handle negative numbers
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
