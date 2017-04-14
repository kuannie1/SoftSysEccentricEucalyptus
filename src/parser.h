#ifndef parser_h
# define parser_h

typedef enum function{
    ADD,
    MULT,
    FLT //pretty sure INT is a keyword
} Function;

typedef union ast_val{
    float flt;
}AstVal;

typedef struct ast_node{
    Function func;
    struct exp *left, *right;
    AstVal *value;
}Ast_Node;

#endif
