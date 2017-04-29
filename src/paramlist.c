/* 
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "paramlist.h"

/* Makes a new node structure.
 * 
 * val: value to store in the node.
 * next: pointer to the next node
 *
 * returns: pointer to a new node
 */
ParamNode *make_param_node_float(char* name, float val, ParamNode *next) {
    ParamNode *node = malloc(sizeof(ParamNode));
    node->param_name = name;
    node->val_flt = val;
    node->func = FLT;
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


/* Removes and returns the first element of a list.
 * 
 * list: pointer to pointer to ParamNode
 *
 * returns: int or -1 if the list is empty
 */
char* pop_param(ParamNode **list) {
    ParamNode *current = *list;

    if (current == NULL) {
        return "";
    }

    char* headVal = current -> param_name;

    **list = *(current->next);

    return headVal;
}


/* Adds a new element to the beginning of the list.
 * 
 * list: pointer to pointer to ParamNode
 * val: value to add
 */
void push_param_float(ParamNode **list, char* name, float val) {
    ParamNode *newElement = make_param_node_float(name, val, *list);
    *list = newElement; //the list points to this new element node
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
