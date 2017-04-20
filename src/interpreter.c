#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

char *get_code(char* filename){
    FILE *file = fopen(filename, "r");
    fseek(file, 0, SEEK_END); // go to end of file
    long int file_length = ftell(file) + 1; // ftell gets the current index
    fseek(file, 0, SEEK_SET); // go to beginning of file

    char* code = malloc(file_length);
    fgets(code, file_length, file);

    fclose(file);
    return code;
}

void free_code(char* code){
    free(code);
}

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
    }
    perror("why are we here");
    exit(-1);
}

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "A filename must be inputed as an argument");
        exit(1);
    }
    char* filename = argv[1];
    char* code = get_code(filename);

    //TODO: pass to parser/lexer, get AST
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

    float expression = eval(ast);
    printf("%f\n", expression);

    return 0;
}