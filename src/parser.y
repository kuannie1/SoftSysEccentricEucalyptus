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
    char* name;
    char* keyword;
}

%token <f> NUM
%type <node> exp S
%token <name> VNAME
%token <keyword> LET_KW
// Make another one that's for defun later
%%

S : exp             {ast = $1; return 0;}
  ;

exp : NUM                                           {$$ = make_ast_node_value((void*) &$1, FLT);}
    | '(' '*' exp exp ')'                           {$$ = make_ast_node_function(MULT, $3, $4);}
    | '(' '+' exp exp ')'                           {$$ = make_ast_node_function(ADD, $3, $4);}
    | '(' '-' exp exp ')'                           {$$ = make_ast_node_function(SUBTR, $3, $4);}
    | '(' '/' exp exp ')'                           {$$ = make_ast_node_function(DIV, $3, $4);}
    | '(' exp ')'                                   {$$ = $2;}
    | '(' LET_KW '(' '(' VNAME exp ')' ')' exp ')'  {$$ = make_ast_node_variable($5, $6, $9);}
    | VNAME                                         {$$ = make_ast_node_value((void*) $1, VARNAME);}                 
    ;

%%

/* make_ast_node_function creates an ast node that represents
 * a calculator like function such as additon, or multiplication.
 *
 * Args:
 *  type: enum Type, in this case, specifying the operator
 *  left: pointer to the left ast_node operand
 *  right: pointer to the right ast_node operand
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
AstNode* make_ast_node_function(Type type, AstNode* left, AstNode* right){
    AstNode* node = malloc(sizeof(AstNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->next = NULL;
    return node;
}

/* make_ast_node_value creates an ast node that holds
 * a value
 *
 * Args:
 *  value: value that ast_node should hold
 *  type: enum Type, either a float or variable name
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
AstNode* make_ast_node_value(void* value, Type type){
    AstNode* node = malloc(sizeof(AstNode));
    node->type = type; 
    if (type == FLT) {
        node->val_flt = *(float*) value;
    } else if (type == VARNAME) {
        node->val_name = (char*) value;
    }
    
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    node->next = NULL;
    return node;
}

/* make_ast_node_variable creates an ast node that holds
 * a variable
 *
 * Args:
 *  vname: variable name as a string
 *  var_value: pointer to an ast_node, what is assigned to the variable
 *  exp: pointer to an ast_node
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
AstNode* make_ast_node_variable(char* vname, AstNode* var_value, AstNode* exp){
    AstNode* node = malloc(sizeof(AstNode));
    node->type = LET; 
    node->val_exp = var_value;
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    node->next = exp;
    node->name = vname;
    return node;
}

void yyerror(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/* build_tree builds an abstract syntax tree given a file descriptor
 *
 * Args:
 *  code: a file descriptor containing lisp code
 *
 * Returns:
 *  ast: pointer to the head AstNode
 */
AstNode* build_tree(FILE* code){
    yyin = code;
    yyparse();
    return ast;
}

// int main() {
//      printf("%i\n", yyparse());
//      printf("%i\n", ast->type);
//      return 0;
// }
