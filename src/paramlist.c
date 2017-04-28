/* 
*/

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
typedef struct node {
    char* param_name;
    union {
        float val_flt;
    };
    Type func;
    struct node *next;
} Node;



/* Makes a new node structure.
 * 
 * val: value to store in the node.
 * next: pointer to the next node
 *
 * returns: pointer to a new node
 */
Node *make_node_float(char* name, float val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->param_name = name;
    node->val_flt = val;
    node->func = FLT;
    node->next = next;
    return node;
}


/* Prints the values in a list.
 * 
 * list: pointer to pointer to Node
 */
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%s ", current->param_name);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
 * 
 * list: pointer to pointer to Node
 *
 * returns: int or -1 if the list is empty
 */
char* pop(Node **list) {
    Node *current = *list;

    if (current == NULL) {
        return "";
    }

    char* headVal = current -> param_name;

    **list = *(current->next);

    return headVal;
}


/* Adds a new element to the beginning of the list.
 * 
 * list: pointer to pointer to Node
 * val: value to add
 */
void push_float(Node **list, char* name, float val) {
    Node *newElement = make_node_float(name, val, *list);
    *list = newElement; //the list points to this new element node
}


// int main() {
//     Node *node = make_node_float("x", 1, NULL);
//     Node **first = &node;
//     print_list(first);
//     push_float(first, "y", 2);
//     print_list(first);
//     pop(first);
//     print_list(first);
//     return 0;
// }
