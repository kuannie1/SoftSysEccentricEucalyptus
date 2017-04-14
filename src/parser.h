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
<<<<<<< HEAD
    struct ast_node* left;
    struct ast_node* right;
=======
    struct exp *left, *right;
>>>>>>> 11604769fb32177fdb514bb46a8ecce43ae3f715
    AstVal *value;
}Ast_Node;

#endif
