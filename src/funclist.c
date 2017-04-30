/* Funclist.c
 *
 * Funclist.c contains functions to manipulate
 * FuncNodes, a type of linkedlist for
 * functions, defined in funclist.h.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#include "parser.h"
#include "funclist.h"
#include <stdlib.h>
#include <stdio.h>

/* Makes a new node structure.
 *
 * Args:
 *  name: the name of the variable
 *  parameters: the parameters as an array of strings
 *  exp: the function body
 *  next: the node that follows this
 *
 * Returns:
 *  node: the pointer to the new node
 */
FuncNode *make_func_node(char* name, char** parameters, AstNode* exp, FuncNode* next){
    FuncNode* func = malloc(sizeof(FuncNode));
    func->func_name = name;
    func->parameters = parameters;
    func->exp = exp;
    func->next = next;
    return func;
}

/* Frees a node structure
 *
 * Args:
 *  node: the node to free
 */
void free_func_node(FuncNode* node){
    free(node);
}

/* Allocates a string array to store the function parameters in
 *
 * Args:
 *  num_params: the number of parameters needed
 *
 * Returns: and empty string array that can hole num_params
 * number of strings
 */
char** make_param_arr(int num_params){
    char** arr = malloc(sizeof(char*)*num_params);
    return arr;
}

/* Frees a string array that stored function parameters
 *
 * Args:
 *  param_arr: the array to free
 */
void free_param_arr(char** param_arr){
    free(param_arr);
}

/* Prints the values in a list.
 * 
 * list: pointer to pointer to FuncNode
 */
void print_func_list(FuncNode **list){
    FuncNode *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%s ", current->func_name);
        current = current->next;
    }
    printf("]\n");
}

/* Removes the first function of a list and
 * returns the function name removed.
 *
 * Args:
 *  list: list to pop from
 *
 * Returns:
 *  name: the name of the removed function
 */
char* pop_func(FuncNode **list){
    FuncNode *current = *list;

    if (current == NULL) {
        return "";
    }

    char* headVal = current -> func_name;

    *list = current->next;

    return headVal;
}

/* Adds a new element to the beginning of the list.
 *
 * Args:
 *  list: list to push to
 *  node: node to push
 */
void push_func(FuncNode **list, FuncNode* node){
    node->next = *list;
    *list = node;
}

/* Looks through the given list to find the matching function
 * name, and returns the corresponding node
 *
 * Args:
 *  functions: list to look through
 *  func_name: name of the function to look for
 *
 * Returns:
 *  node: the FuncNode of the correct function
 */
FuncNode* get_function(FuncNode** functions, char* func_name){
    FuncNode *current = *functions;
    while (current != NULL){
        if (strcmp(current->func_name, func_name) == 0) {
            return current;
        }
        current = current->next;
    }
    perror("function does not exist");
    exit(-1);
}
