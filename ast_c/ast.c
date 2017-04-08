/* 
Abstract Syntax Tree implementation in C, from Leonidas Ferigas.
https://lambda.uta.edu/cse5317/notes/node23.html

This code represents an abstract syntax tree, with make functions for each of the types of expressions.
*/

#include <stdlib.h>
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

ast* make_callExp( char* name, ast_list* arguments ) {
	ast* e = malloc(sizeof(ast));
	e->tag = call_exp;
	e->op.callExp.name = name;
	e->op.callExp.arguments = arguments;
	return e;
}

ast* make_projectionExp( ast* record, char* attribute ) {
	ast* e = malloc(sizeof(ast));
	e->tag = projection_exp;
	e->op.projectionExp.record = record;
	e->op.projectionExp.attribute = attribute;
	return e;
}

ast* make_recordExp( char* attribute, ast* value, struct rec* next ) {
	ast* e = malloc(sizeof(ast));
	e->tag = record_exp;
	e->op.recordExp.attribute = attribute;
	e->op.recordExp.value = value;
	e->op.recordExp.next = next;
	return e;
}