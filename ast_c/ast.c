/* 
Abstract Syntax Tree implementation in C, from Leonidas Ferigas.
https://lambda.uta.edu/cse5317/notes/node23.html
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

ast *make_integerExp( int integerExp) {
	ast *e = malloc(sizeof(ast));
	e->tag = integer_exp;
	e->op.integerExp = integerExp;
	return e;
}
