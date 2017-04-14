%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern int yylex();
void yyerror(char *msg);
%}

%union {
  float f;
}

%token <f> NUM
%type <f> exp

%%

S : F           {printf("%f\n", $1);} // Print out final value
  ;

A : '(' '+'     {$$ = 0;} // Initialize A token with value 0
  | A F         {$$ = $1 + $2;} // Subsequent F tokens are added to A token
  ;

exp : NUM                  {$$ = ();} // All NUM's become F token
    | '(' '*' exp exp ')'  {$$ = make_ast_node_function(MULT, $3, $4)}
    | '(' '+' exp exp ')'
    ;


%%

Ast_Node* make_ast_node_function(Function funct, Ast_){
  Ast_Node* new_function
}

void yyerror(char *msg){
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main() {
  yyparse();
  return 0;
}
