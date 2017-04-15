#ifndef parser_h
#define parser_h

typedef enum function{
    ADD,
    MULT,
    FLT
} Function;

typedef union ast_val{
    float flt;
}AstVal;

typedef struct ast_node{
    Function func;
    struct exp *left, *right;
    AstVal *value;
}Ast_Node;

Ast_Node* make_ast_node_function(Function func, Ast_Node* left, Ast_Node* right);
Ast_Node* make_ast_node_value(float value);

#endif
