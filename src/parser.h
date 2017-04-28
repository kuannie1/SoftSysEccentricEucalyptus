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
    LAMBDA
} Function;

typedef union ast_val{
    float flt;
}AstVal;

/* ast_node struct serves as the building block of our abstract
 * syntax tree.
 *
 * Members:
 *  func: enum Function type
 *  left: pointer to an ast_node
 *  right: pointer to an ast_node
 *  value: numerical union
 */
typedef struct ast_node{
    Function func;
    struct ast_node *left, *right;
    AstVal *value;
}Ast_Node;

Ast_Node* make_ast_node_function(Function func, Ast_Node* left, Ast_Node* right);
Ast_Node* make_ast_node_value(float value);
Ast_Node* build_tree(FILE* code);

#endif
