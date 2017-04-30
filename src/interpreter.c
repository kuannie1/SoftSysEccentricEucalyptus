/* Interpreter.c
 *
 * Interpreter.c is a lisp interpreter capable of basic calculations,
 * typetion declarations, and variable usage.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 * Usage:
 *  make interpreter
 *  ./interpreter test.lisp
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paramlist.h"
#include "parser.h"
#include "funclist.h"

// forward declaration, so `eval_param` can call `eval`
float eval(AstNode* ast, ParamNode** vars, FuncNode** functions);

/* Given a variable node (type must be LET), adds the
 * variable into the environment (list of variables)
 * and evaluates the rest of the tree branch normally.
 * Afterwards, it removes itself from the environment.
 *
 * Args:
 *  ast: pointer to the head AstNode
 *  vars: list of variables and their values currently
 *          in the environment
 *  functions: list of functions currently in use
 *
 * Returns:
 *  flt: final value of evaluation
 */
float eval_param(AstNode* ast, ParamNode** vars, FuncNode** functions){
    if (ast->type != LET)
        perror("To use `eval_param`, the top level Ast_Node must have type `LET`");
    float var_val = eval(ast->val_exp, vars, functions);
    push_param_float(vars, ast->name, var_val);
    float result = eval(ast->next, vars, functions);
    pop_param(vars);
    return result;
}

/* eval recursively evaluates an abstract syntax tree
 *
 * Args:
 *  ast: pointer to the head AstNode
 *  vars: list of variables and their values currently
 *          in the environment
 *  functions: list of functions currently in use
 *
 * Returns:
 *  flt: final value of evaluation
 */
float eval(AstNode* ast, ParamNode** vars, FuncNode** functions){
    // return value
    if(ast->type == FLT){
        return ast->val_flt;
    }

    if (ast->type == VARNAME) {
        char* variable_name = ast->val_name;
        return get_value(vars, variable_name);
    }

    // evaluate some stuff
    if (ast->type == LET) {
        return eval_param(ast, vars, functions);
    }

    if(ast->type == FUNC){
        char* function_name = ast->name;
        FuncNode* function = get_function(functions, function_name);
        AstNode* function_param = make_ast_node_variable(function->parameters[0],
                                                        ast->val_exp, function->exp);
        return eval_param(function_param, vars, functions);
    }

    // binary functions
    float left_val = eval(ast->left, vars, functions);
    float right_val = eval(ast->right, vars, functions);


    switch(ast->type){
        case MULT:  return left_val * right_val;
        case ADD:   return left_val + right_val;
        case SUBTR: return left_val - right_val;
        case DIV:   return left_val / right_val;
        default:
            perror("why are we here");
            exit(-1);
    }
}


int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "A filename must be inputed as an argument");
        exit(1);
    }
    char* filename = argv[1];
    FILE *file = fopen(filename, "r");
    AstNode** ast = malloc(sizeof(AstNode*));
    FuncNode** funclist = malloc(sizeof(FuncNode*));
    build_tree(file, ast, funclist);
    float expression = eval(*ast, malloc(sizeof(ParamNode*)), funclist);
    printf("%f\n", expression);

    return 0;
}
