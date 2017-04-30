#ifndef paramlist_h
#define paramlist_h

#include "parser.h"
typedef struct param_node {
    char* param_name;
    union {
        float val_flt;
    };
    Type func;
    struct param_node *next;
} ParamNode;

ParamNode *make_param_node_float(char* name, float val, ParamNode *next);
void print_param_list(ParamNode **list);
char* pop_param(ParamNode **list);
void push_param_float(ParamNode **list, char* name, float val);

#endif