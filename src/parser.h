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

typedef struct exp{
    Function func;
    struct exp* left, right;
    AstVal *value;
}Exp;

#endif
