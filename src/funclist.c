#include "parser.h"
#include "funclist.h"
#include <stdlib.h>
#include <stdio.h>


FuncNode *make_func_node(char* name, char** parameters, AstNode* exp, FuncNode* next){
    FuncNode* func = malloc(sizeof(FuncNode));
    func->func_name = name;
    func->parameters = parameters;
    func->exp = exp;
    func->next = next;
    return func;
}
void free_func_node(FuncNode* node){
    free(node);
}
char** make_param_arr(int num_params){
    char** arr = malloc(sizeof(char*)*num_params);
    return arr;
}
void free_param_arr(char** param_arr){
    free(param_arr);
}
void print_func_list(FuncNode **list){
    FuncNode *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%s ", current->func_name);
        current = current->next;
    }
    printf("]\n");
}
char* pop_func(FuncNode **list){
    FuncNode *current = *list;

    if (current == NULL) {
        return "";
    }

    char* headVal = current -> func_name;

    *list = current->next;

    return headVal;
}
void push_func(FuncNode **list, FuncNode* node){
    node->next = *list;
    *list = node;
}
