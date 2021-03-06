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
    char* name;
    char* keyword;
}

%token <f> NUM
%type <node> exp S
%type <func> decl
%token <name> NAME
%token <keyword> LET_KW DEFUN_KW POW_KW
%%

S : decls exp             {ast = $2; return 0;}
  ;

decls : /*empty*/
      | decls decl

decl : '(' DEFUN_KW NAME '(' NAME ')' exp ')'       {$$ = make_func($3, $5, $7); free($2);}

exp : NUM                                           {$$ = make_ast_node_value((void*) &$1, FLT);}
    | '(' '*' exp exp ')'                           {$$ = make_ast_node_function(MULT, $3, $4);}
    | '(' '+' exp exp ')'                           {$$ = make_ast_node_function(ADD, $3, $4);}
    | '(' '-' exp exp ')'                           {$$ = make_ast_node_function(SUBTR, $3, $4);}
    | '(' '/' exp exp ')'                           {$$ = make_ast_node_function(DIV, $3, $4);}
    | '(' POW_KW exp exp ')'                        {$$ = make_ast_node_function(POWER, $3, $4);}
    | '(' exp ')'                                   {$$ = $2;}
    | '(' LET_KW '(' '(' NAME exp ')' ')' exp ')'   {$$ = make_ast_node_variable($5, $6, $9); free($2);}
    | NAME                                          {$$ = make_ast_node_value((void*) $1, VARNAME);}
    | '(' NAME exp ')'                              {$$ = make_ast_node_func($2, $3);}
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


/* make_ast_node_func creates an ast node that references a function
 *
 * Args:
 *  func: function name
 *  var_value: the value of the parameter to pass in
 *
 * Returns:
 *  node: pointer to the newly created ast_node
 */
AstNode* make_ast_node_func(char* func, AstNode* var_value){
    AstNode* node = malloc(sizeof(AstNode));
    node->type = FUNC; 
    node->val_exp = var_value; //THIS IS AN AWFUL IDEA AND NOT SCALABLE
    node->left = NULL; // values don't have progeny
    node->right = NULL;
    node->next = NULL;
    node->name = func;
    return node;
}

/* make_func makes a FuncNode, pushes it to the list of functions,
 * then returns the newly created FuncNode.
 *
 * Args:
 *  name: function name as a string
 *  parameter: parameter name as a string
 *  exp: pointer to the function body
 *
 * Returns:
 *  func: pointer to the newly created FuncNode
 */
FuncNode* make_func(char* name, char* parameter, AstNode* exp){
    char** param_arr = make_param_arr(1);
    param_arr[0] = parameter;
    FuncNode* func = make_func_node(name, param_arr, exp, NULL, 1);
    push_func(funclist, func);
    return func;
}

void yyerror(char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(1);
}


/* build_tree builds an abstract syntax tree given a file descriptor
 *
 * Args:
 *  code: a file descriptor containing lisp code
 *  ast_pointer: pointer to AstNode to pack
 *  func_list_pointer: pointer to funclist to pack
 */
void build_tree(FILE* code, AstNode** ast_pointer, FuncNode** func_list_pointer){
    yyin = code;
    funclist = malloc(sizeof(FuncNode*));
    yyparse();
    *ast_pointer = ast;
    *func_list_pointer = *funclist;
}

/* Frees an AstNode tree
 * 
 * Args:
 *  node: the head of the tree to free
 */
void free_tree(AstNode* node){
    if(node->left != NULL){
        free_tree(node->left);
    }
    if(node->right != NULL){
        free_tree(node->right);
    }
    if(node->next != NULL){
        free_tree(node->next);
    }
    switch(node->type){
        case FUNC:
            free_tree(node->val_exp);
            free(node->name);
            break;
        case LET:
            free_tree(node->val_exp);
            free(node->name);
            break;
        case VARNAME:
            free(node->val_name);
            break;
        default: break;
    }
    free(node);
}

// int main() {
//      printf("%i\n", yyparse());
//      printf("%i\n", ast->type);
//      return 0;
// }
