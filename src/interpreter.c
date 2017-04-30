/* Interpreter.c
 *
 * Interpreter.c is a lisp interpreter capable of basic calculations,
 * function declarations, and variable usage.
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
float eval(Ast_Node* ast, ParamNode** vars, FuncNode** functions);

float eval_param(Ast_Node* ast, ParamNode** vars, FuncNode** functions){
    float var_val = eval(ast->val_exp, vars, functions);
    push_param_float(vars, ast->name, var_val);
    float result = eval(ast->next, vars, functions);
    pop_param(vars);
    return result;
}

/* eval recursively evaluates an abstract syntax tree
 *
 * Args:
 *  ast: pointer to the head Ast_Node
 *
 * Returns:
 *  flt: final value of evaluation
 */
float eval(Ast_Node* ast, ParamNode** vars, FuncNode** functions){
    // return value
    if(ast->func == FLT){
        return ast->val_flt;
    }
    if (ast->func == LET) {
        float var_val = eval(ast->val_exp, vars, functions);
        push_param_float(vars, ast->name, var_val);
        float result = eval(ast->next, vars, functions);
        pop_param(vars);
        return result;
    }

    if (ast->func == VARNAME) {
        char* variable_name = ast->val_name;
        ParamNode *current = *vars;
        while (current != NULL){
            if (strcmp(current->param_name, variable_name) == 0) {
                return current->val_flt;
            }
            current = current->next;
        }
        perror("variable name does not exist");
        exit(-1);
    }

    if(ast->func == FUNC){
        char* function_name = ast->name;
        FuncNode *current = *functions;
        while (current != NULL){
            if (strcmp(current->func_name, function_name) == 0) {
                Ast_Node* function_param = make_ast_node_variable(current->parameters[0],
                                                        ast->val_exp, current->exp);
                return eval_param(function_param, vars, functions);
            }
            current = current->next;
        }
        perror("function does not exist");
        exit(-1);
    }

    // binary functions
    float left_val = eval(ast->left, vars, functions);
    float right_val = eval(ast->right, vars, functions);

    switch(ast->func){
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
    Ast_Node** ast = malloc(sizeof(Ast_Node*));
    FuncNode** funclist = malloc(sizeof(FuncNode*));
    build_tree(file, ast, funclist);
    float expression = eval(*ast, malloc(sizeof(ParamNode*)), funclist);
    printf("%f\n", expression);

    return 0;
}
