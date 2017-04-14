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

typedef struct exp{
    Function func;
    struct exp *left, *right;
    AstVal *value;
}Exp;

#endif
