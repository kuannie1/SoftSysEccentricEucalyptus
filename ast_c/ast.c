/* 
Abstract Syntax Tree implementation in C, from Leonidas Ferigas.
https://lambda.uta.edu/cse5317/notes/node23.html
*/

#include <stdlib.h>

typedef struct Exp {

	enum { integer_exp, string_exp, variable_exp,
		binary_exp, unary_exp, call_exp,
		projection_exp, record_exp } tag;

	union {
		int integerExp;
		char* stringExp;
		char* variableExp;
		//a binary operation (ike addition, subtraction, multiplication, division)
		struct {char* operator;
			struct Exp* left;
			struct Exp* right; } binaryExp;
		//a unary operation (like a negative sign)
		struct { char* operator;
			struct Exp* operand; } unaryExp;
		//a call operation (like a function???)
		struct { char* name;
			struct Exp_list* arguments; } callExp;
		//projection operation (still trying to figure out what this means)
		struct {struct Exp* record;
			char* attribute; } projectionExp;
		//also not sure what this is
		struct rec { char* attribute;
			struct Exp* value;
			struct rec* next; } recordExp;
	} op;

} ast;

typedef struct Exp_list { 
  ast*             elem;
  struct Exp_list* next;
} ast_list;

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

ast* make_callExp( char* name, ast_list* arguments );
ast* make_projectionExp( char* record, char* attribute);

int main() {

	ast* additionexp = make_binaryExp("+", make_integerExp(5), make_integerExp(7)); //represents 5+7

return 0;
}
