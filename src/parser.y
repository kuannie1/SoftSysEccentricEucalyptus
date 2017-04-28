/* Parser.y
 *
 * Parser.y contains the code and gramatical rules
 * that will build the abstract syntax tree used by our
 * interpreter.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

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

S : exp             {ast = $1; return 0;}
  ;

exp : NUM                  {$$ = make_ast_node_value($1);}
    | '(' '*' exp exp ')'  {$$ = make_ast_node_function(MULT, $3, $4);}
    | '(' '+' exp exp ')'  {$$ = make_ast_node_function(ADD, $3, $4);}
    | '(' '-' exp exp ')'  {$$ = make_ast_node_function(SUBTR, $3, $4);}
    | '(' '/' exp exp ')'  {$$ = make_ast_node_function(DIV, $3, $4);}
    | '(' exp ')'          {$$ = $2;}
    ;

%%

/* make_ast_node_function creates an ast node that represents
 * a calculator like function such as additon, or multiplication.
 *
 * Args:
 *  func: enum Function
 *  left: pointer to an ast_node
 *  right: pointer to an ast_node
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
Ast_Node* make_ast_node_function(Function func, Ast_Node* left, Ast_Node* right){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = func;
    node->value = NULL;
    node->left = left;
    node->right = right;
    return node;
}

/* make_ast_node_value creates an ast node that holds
 * a value
 *
 * Args:
 *  value: numerical value that ast_node should hold
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
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

/* build_tree builds an abstract syntax tree given stdin data flow
 *
 * Args:
 *  code: a file descriptor - stdin for our usage
 *
 * Returns:
 *  ast: pointer to the head Ast_Node
 */
Ast_Node* build_tree(FILE* code){
    yyin = code;
    yyparse();
    return ast;
}

// int main() {
//      printf("%i\n", yyparse());
//      printf("%i\n", ast->func);
//      return 0;
// }
