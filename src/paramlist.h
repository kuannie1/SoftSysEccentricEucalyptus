/* Paramlist.h
 *
 * Paramlist.h is a header file that declares and defines the
 * the ParamNode structure, to store lists of variables and
 * their values.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

#ifndef paramlist_h
#define paramlist_h

#include "parser.h"

/* param_node struct stores a single variable name and value
 * pair, and a reference to the next ParamNode
 *
 * Members:
 *  param_name: name of the variable
 *  anonymous union:
 *      val_flt: value of variable. Stored in a union for future
 *                  scalability
 *  type: enum Type, type of variable. Currently can only be a
 *          float; however this field exists for scalability,
 *          along with the union above.
 *  next: reference to the next ParamNode
 */
typedef struct param_node {
    char* param_name;
    union {
        float val_flt;
    };
    Type type;
    struct param_node *next;
} ParamNode;

ParamNode *make_param_node_float(char* name, float val, ParamNode *next);
void print_param_list(ParamNode **list);
char* pop_param(ParamNode **list);
void push_param_float(ParamNode **list, char* name, float val);
float get_value(ParamNode** varlist, char* varname);

#endif