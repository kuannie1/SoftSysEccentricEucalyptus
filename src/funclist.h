#ifndef funclist_h
#define funclist_h

#include "parser.h"


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

#endif