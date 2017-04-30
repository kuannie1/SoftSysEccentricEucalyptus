/* Parser.h
 *
 * Parser.h is a header file that declares and defines the enums,
 * functions, unions, and structs that will be used in parser.y
 * and throughout the project. It defines the structure of the
 * Abstract Syntax Tree.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include "funclist.h"

/* Type is an enum that stores the type of AstNode. Includes
 * operators such as add, multiply, subtract; data types such
 * as float; and other functions such as let.
 */
typedef enum{
    ADD,
    MULT,
    SUBTR,
    DIV,
    POWER,
    FLT,
    LET,
    VARNAME,
    FUNC
} Type;

/* ast_node struct serves as the building block of our abstract
 * syntax tree.
 *
 * Members:
 *  type: enum Type, the type of Node
 *  left: pointer to an ast_node
 *  right: pointer to an ast_node
 *  anonymous union:
 *      val_flt, val_exp, val_name: storing values of different
 *                                  types
 *  name: used if the node can be identified with a name (in
 *          the case of let)
 *  next: if there is a continuation of a tree that does not
 *      fit in the left/right node structure. For example, in
 *      let, there is a body of code for which the new variable
 *      is part of the environment.
 */
typedef struct ast_node{
    Type type;
    struct ast_node *left, *right;
    union {
        float val_flt;
        struct ast_node* val_exp;
        char* val_name;
    };
    char* name;
    struct ast_node *next;
}AstNode;


AstNode* make_ast_node_function(Type func, AstNode* left, AstNode* right);
AstNode* make_ast_node_value(void* value, Type func);
AstNode* make_ast_node_variable(char* vname, AstNode* var_value, AstNode* exp);
AstNode* make_ast_node_func(char* func, AstNode* var_value);
FuncNode* make_func(char* name, char* parameter, AstNode* exp);
void build_tree(FILE* code, AstNode** ast_pointer, FuncNode** func_list_pointer);
void free_tree(AstNode* node);

#endif
