/*
Evaluates an abstract syntax tree in C, using the ast struct by Leonidas Farigas. 
Currently supports: addition, subtraction, multiplication, divition, negative numbers, integer variables.
By Margo Crawford.

*/
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "ast.h"

GHashTable* hash; 

int parser(ast* expression) {
	//binary expression
	if (expression-> tag == binary_exp) {
		//recursively parse the left and right expressions.
		ast* leftExp = expression -> op.binaryExp.left;
		int leftside = parser(leftExp);
		ast* rightExp = expression-> op.binaryExp.right;
		int rightside = parser(rightExp);
		//perform an operation.
		char* operator = expression->op.binaryExp.operator;
		if (operator == "+") {
			return rightside + leftside;
		}
		else if (operator == "-") {
			return rightside - leftside;
		} else if (operator == "*") {
			return rightside * leftside;
		} else if (operator == "/") {
			return rightside / leftside;
		} else {
			printf("You entered binary operator %s. This isnt supported yet.", operator);
		}
	}
	//unary expression
	else if (expression->tag == unary_exp) {
		//recursively parse the child expression.
		ast* childExp = expression->op.unaryExp.operand;
		int child = parser(childExp);
		//perform an operation.
		if (expression->op.unaryExp.operator == "-") {
			return child * -1;
		}
	}
	//integer.
	else if (expression->tag == integer_exp) {
		return expression->op.integerExp;
	}
	//variable
	else if (expression->tag == variable_exp ) {
		gpointer* val = g_hash_table_lookup(hash, expression->op.variableExp);
		if (val != NULL) {
			return GPOINTER_TO_INT(val);
		}
	}
}



int main() {

	hash = g_hash_table_new(g_str_hash, g_str_equal); //a hashtable with strings as keys.

	ast* variable = make_variableExp("x");
	g_hash_table_insert(hash, "x", GINT_TO_POINTER(6));

	//x = 6
	//(-5+7) * x
	ast* additionexp = make_binaryExp("*", make_binaryExp("+", make_unaryExp("-", make_integerExp(5)), make_integerExp(7)), variable);
	int retval = parser(additionexp);
	printf("%i\n", retval);
	return 0;
}
