#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

float eval(Ast_Node* ast){
    // return value
    if(ast->func == FLT){
        return ast->value->flt;
    }

    // binary functions
    float left_val = eval(ast->left);
    float right_val = eval(ast->right);

    switch(ast->func){
        case MULT:  return left_val * right_val;
        case ADD:   return left_val + right_val;
        case SUBTR: return left_val - right_val;
        case DIV:   return left_val / right_val;
    }
    perror("why are we here");
    exit(-1);
}

Ast_Node* make_test_tree(){
    Ast_Node* ast = malloc(sizeof(Ast_Node));
    ast->func = ADD;
    ast->left = malloc(sizeof(Ast_Node));
    ast->right = malloc(sizeof(Ast_Node));

    ast->left->func = FLT;
    ast->left->value = malloc(sizeof(AstVal));
    ast->left->value->flt = 5.5;
    ast->right->func = FLT;
    ast->right->value = malloc(sizeof(AstVal));
    ast->right->value->flt = 6;
    return ast;
}

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "A filename must be inputed as an argument");
        exit(1);
    }
    char* filename = argv[1];
    FILE *file = fopen(filename, "r");
    Ast_Node* ast = build_tree(file);

    float expression = eval(ast);
    printf("%f\n", expression);

    return 0;
}