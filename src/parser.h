/* Parser.h
 *
 * Parser.h is a header file that declares and defines the enums,
 * functions, unions, and structs that will be used in Parser.y
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#ifndef parser_h
#define parser_h

#include <stdio.h>

typedef enum function{
    ADD,
    MULT,
    SUBTR,
    DIV,
    FLT,
    LET,
    VARNAME,
    LAMBDA
} Type;

/* ast_node struct serves as the building block of our abstract
 * syntax tree.
 *
 * Members:
 *  func: enum Type type
 *  left: pointer to an ast_node
 *  right: pointer to an ast_node
 *  value: numerical union
 */
typedef struct ast_node{
    Type func;
    struct ast_node *left, *right;
    union {
        float val_flt;
        struct ast_node* val_exp;
        char* val_name;
    };
    char* name;
    struct ast_node *next;
}Ast_Node;

Ast_Node* make_ast_node_function(Type func, Ast_Node* left, Ast_Node* right);
Ast_Node* make_ast_node_value(void* value, Type func);
Ast_Node* make_ast_node_variable(char* vname, Ast_Node* var_value, Ast_Node* exp);
Ast_Node* build_tree(FILE* code);

#endif
