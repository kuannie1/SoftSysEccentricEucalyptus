#ifndef parser_h
# define parser_h

typedef enum function{
    ADD,
    MULT,
    INTEGER //pretty sure INT is a keyword
} Function;

typedef union ast_val{
    int integer;
}AstVal;

typedef struct ast_node{
    Function func;
    struct ast_node* left;
    struct ast_node* right;
    AstVal *value;
}Ast_Node;

#endif
