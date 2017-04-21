%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern int yylex();
extern FILE *yyin;
void yyerror(char *msg);

struct ast_node* ast;
%}

%union {
    float f;
    struct ast_node* node; //can't use typedefs here for some reason
}

%token <f> NUM
%type <node> exp S

%%

S : exp             {ast = $1; return 0;} // Print out final value
  ;

exp : NUM                  {$$ = make_ast_node_value($1);}
    | '(' '*' exp exp ')'  {$$ = make_ast_node_function(MULT, $3, $4);}
    | '(' '+' exp exp ')'  {$$ = make_ast_node_function(ADD, $3, $4);}
    | '(' exp ')'          {$$ = $2;}
    ;

%%

Ast_Node* make_ast_node_function(Function func, Ast_Node* left, Ast_Node* right){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = func;
    node->value = NULL;
    node->left = left;
    node->right = right;
    return node;
}

Ast_Node* make_ast_node_value(float value){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = FLT; // values are always floats
    node->value = malloc(sizeof(AstVal));
    node->value->flt = value;
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    return node;
}

void yyerror(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

Ast_Node* build_tree(FILE* code){
    yyin = code;
    do {
        yyparse();
    } while (!feof(yyin));
    return ast;
}

int main() {
    printf("%i\n", yyparse());
    printf("%i\n", ast->func);
    return 0;
}
