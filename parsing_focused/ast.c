/* 
Abstract Syntax Tree implementation in C, from Leonidas Ferigas.
https://lambda.uta.edu/cse5317/notes/node23.html

This code represents an abstract syntax tree, with make functions for each of the types of expressions.
*/

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

ast *make_binaryExp ( char* operator, ast* left, ast* right ) {
	ast *e = malloc(sizeof(ast));
	e->tag = binary_exp;
	e->op.binaryExp.operator = operator;
	e->op.binaryExp.left = left;
	e->op.binaryExp.right = right;
	return e;
};

ast *make_unaryExp( char* operator, ast* operand ) {
	ast *e = malloc(sizeof(ast));
	e->tag = unary_exp;
	e->op.unaryExp.operator = operator;
	e->op.unaryExp.operand = operand;
	return e;
}

ast *make_integerExp( int integerExp ) {
	ast *e = malloc(sizeof(ast));
	e->tag = integer_exp;
	e->op.integerExp = integerExp;
	return e;
}

ast* make_stringExp( char* stringExp ) {
	ast* e = malloc(sizeof(ast));
	e->tag = string_exp;
	e->op.stringExp = stringExp;
	return e;
}

ast* make_variableExp( char* variableExp ) {
	ast* e = malloc(sizeof(ast));
	e->tag = variable_exp;
	e->op.variableExp = variableExp;
	return e;
}

ast* make_conditionalExp( ast* condition, ast* left, ast* right ) {
	ast* e = malloc(sizeof(ast));
	e->tag = conditional_exp;
	e->op.conditionalExp.condition = condition;
	e->op.conditionalExp.left = left;
	e->op.conditionalExp.right = right;
	return e;
}

ast* make_functionExp( char* name, ast* func, int num_arguments, char* arguments[] ) {
	ast* e = malloc(sizeof(ast) + num_arguments*sizeof(char*));
	e->tag = function_exp;
	e->op.functionExp.name = name;
	e->op.functionExp.func = func;
	e->op.functionExp.num_arguments = num_arguments;
	for (int i = 0; i < num_arguments; i++) {
		e->op.functionExp.arguments[i] = arguments[i];
	}
	return e;
}