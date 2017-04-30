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
#include "funclist.h"

extern int yylex();
extern FILE *yyin;
void yyerror(char *msg);

struct ast_node* ast;
FuncNode** funclist;
%}

%union {
    float f;
    struct ast_node* node; //can't use typedefs here for some reason
    struct func_node* func;
    // char ** param_arr;
    char* name;
    char* keyword;
}

%token <f> NUM
%type <node> exp S
%type <func> decl
// %type <param_arr> params
%token <name> NAME
%token <keyword> LET_KW DEFUN_KW
%%

S : exp             {ast = $1; return 0;}
  ;

decl : '(' DEFUN_KW NAME '(' NAME ')' exp ')'       {make_func($3, $5, $7);}

exp : NUM                                           {$$ = make_ast_node_value((void*) &$1, FLT);}
    | '(' '*' exp exp ')'                           {$$ = make_ast_node_function(MULT, $3, $4);}
    | '(' '+' exp exp ')'                           {$$ = make_ast_node_function(ADD, $3, $4);}
    | '(' '-' exp exp ')'                           {$$ = make_ast_node_function(SUBTR, $3, $4);}
    | '(' '/' exp exp ')'                           {$$ = make_ast_node_function(DIV, $3, $4);}
    | '(' exp ')'                                   {$$ = $2;}
    | '(' LET_KW '(' '(' NAME exp ')' ')' exp ')'   {$$ = make_ast_node_variable($5, $6, $9);}
    | NAME                                          {$$ = make_ast_node_value((void*) $1, VARNAME);}
    | '(' NAME exp ')'                              {$$ = make_ast_node_func($2, $3);}
    ;




%%

/* make_ast_node_function creates an ast node that represents
 * a calculator like function such as additon, or multiplication.
 *
 * Args:
 *  func: enum Type
 *  left: pointer to an ast_node
 *  right: pointer to an ast_node
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
Ast_Node* make_ast_node_function(Type func, Ast_Node* left, Ast_Node* right){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = func;
    node->left = left;
    node->right = right;
    node->next = NULL;
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
Ast_Node* make_ast_node_value(void* value, Type func){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = func; 
    if (func == FLT) {
        node->val_flt = *(float*) value;
    } else if (func == VARNAME) {
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
Ast_Node* make_ast_node_variable(char* vname, Ast_Node* var_value, Ast_Node* exp){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = LET; 
    node->val_exp = var_value;
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    node->next = exp;
    node->name = vname;
    return node;
}


/* 
 *
 * Args:
 *
 * Returns:
 *  
 */
Ast_Node* make_ast_node_func(char* func, Ast_Node* var_value){
    Ast_Node* node = malloc(sizeof(Ast_Node));
    node->func = FUNC; 
    node->val_exp = var_value; //THIS IS AN AWFUL IDEA AND NOT SCALABLE
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    node->next = NULL;
    node->name = func;
    return node;
}

void make_func(char* name, char* parameter, Ast_Node* exp){
    char** param_arr = make_param_arr(1);
    param_arr[0] = parameter;
    push_func(funclist, name, param_arr, exp);
}

void yyerror(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/* build_tree builds an abstract syntax tree given stdin data flow
 * TODO: outdated docs
 * Args:
 *  code: a file descriptor - stdin for our usage
 *
 * Returns:
 *  ast: pointer to the head Ast_Node
 */
void build_tree(FILE* code, Ast_Node** ast_pointer, FuncNode** func_list_pointer){
    yyin = code;
    funclist = malloc(sizeof(FuncNode*));
    yyparse();
    *ast_pointer = ast;
    *func_list_pointer = *funclist;
}

// int main() {
//      printf("%i\n", yyparse());
//      printf("%i\n", ast->func);
//      return 0;
// }
