/* Funclist.h
 *
 * Funclist.h is a header file that declares and defines the
 * the FuncNode structure, to store lists of functions.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#ifndef funclist_h
#define funclist_h

#include "parser.h"

/* func_node struct stores a function name, parameter name(s),
 * a function body, and a reference to the next FuncNode.
 *
 * Members:
 *  func_name: name of the function
 *  parameters: array of parameters, as strings
 *  exp: function body as an abstract syntax tree
 *  next: reference to the next FuncNode
 */
typedef struct func_node {
    char* func_name;
    char** parameters;
    struct ast_node* exp;
    struct func_node *next;
} FuncNode;

FuncNode *make_func_node(char* name, char** parameters, struct ast_node* exp, FuncNode* next);
void free_func_node(FuncNode* node);
char** make_param_arr(int num_params);
void free_param_arr(char** param_arr);
void print_func_list(FuncNode **list);
char* pop_func(FuncNode **list);
void push_func(FuncNode **list, FuncNode* node);
FuncNode* get_function(FuncNode** functions, char* func_name);

#endif