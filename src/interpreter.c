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

float eval(Exp* ast){

}

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "A filename must be inputed as an argument");
        exit(1);
    }
    char* filename = argv[1];
    char* code = get_code(filename);
    puts(code);
return 0;
    //TODO: pass to parser/lexer, get AST
    Exp* ast;

    float expression = eval(ast);

    return 0;
}