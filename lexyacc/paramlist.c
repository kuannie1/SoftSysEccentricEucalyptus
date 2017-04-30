/* Paramlist.c
 *
 * Paramlist.c contains functions to manipulate
 * ParamNodes, a type of linkedlist for
 * variables, defined in paramlist.h.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "paramlist.h"

/* Makes a new node structure.
 *
 * Args:
 *  name: the name of the variable
 *  val: the value of the variable
 *  next: the node that follows this
 *
 * Returns:
 *  node: the pointer to the new node
 */
ParamNode *make_param_node_float(char* name, float val, ParamNode *next) {
    ParamNode *node = malloc(sizeof(ParamNode));
    node->param_name = name;
    node->val_flt = val;
    node->type = FLT;
    node->next = next;
    return node;
}


/* Prints the values in a list.
 * 
 * list: pointer to pointer to ParamNode
 */
void print_param_list(ParamNode **list) {
    ParamNode *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%s ", current->param_name);
        current = current->next;
    }
    printf("]\n");
}


/* Removes the first variable of a list and
 * returns the variable name removed.
 *
 * Args:
 *  list: list to pop from
 *
 * Returns:
 *  name: the name of the removed variable
 */
char* pop_param(ParamNode **list) {
    ParamNode *current = *list;

    if (current == NULL) {
        return "";
    }

    char* name = current -> param_name;

    *list = current->next;
    free(current);

    return name;
}

/* Adds a new element to the beginning of the list.
 *
 * Args:
 *  list: list to push to
 *  name: the name of the variable
 *  val: the value of the variable
 */
void push_param_float(ParamNode **list, char* name, float val) {
    ParamNode *newElement = make_param_node_float(name, val, *list);
    *list = newElement; //the list points to this new element node
}

/* Looks through the given list to find the matching variable name,
 * and returns the corresponding value
 *
 * Args:
 *  varlist: list to look through
 *  varname: name of the variable to look for
 *
 * Returns:
 *  flt: the float represented by the variable name
 */
float get_value(ParamNode** varlist, char* varname){
    ParamNode *current = *varlist;
    while (current != NULL){
        if (strcmp(current->param_name, varname) == 0) {
            return current->val_flt;
        }
        current = current->next;
    }
    perror("variable name does not exist");
    exit(-1);
}

// int main() {
//     ParamNode *node = make_node_float("x", 1, NULL);
//     ParamNode **first = &node;
//     print_list(first);
//     push_float(first, "y", 2);
//     print_list(first);
//     pop(first);
//     print_list(first);
//     return 0;
// }
