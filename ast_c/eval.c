/*
Evaluates an abstract syntax tree in C, using the ast struct by Leonidas Farigas. 
Currently supports: addition, subtraction, multiplication, divition, negative numbers, integer variables.
By Margo Crawford.

*/
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "ast.h"
#include "eval.h"


int eval(ast* expression, GHashTable* vars) {
	//binary expression
	if (expression-> tag == binary_exp) {
		//recursively parse the left and right expressions.
		ast* leftExp = expression -> op.binaryExp.left;
		int leftside = eval(leftExp, vars);
		ast* rightExp = expression-> op.binaryExp.right;
		int rightside = eval(rightExp, vars);
		//perform an operation.
		char* operator = expression->op.binaryExp.operator;
		if (strcmp(operator,"+") == 0) {
			return rightside + leftside;
		}
		else if (strcmp(operator,"-") == 0) {
			return leftside - rightside;
		} else if (strcmp(operator, "*") == 0) {
			return rightside * leftside;
		} else if (strcmp(operator,"/") == 0) {
			return leftside / rightside;
		} else {
			printf("You entered the binary operator %s. This isnt supported yet.\n", operator);
		}
	}
	//unary expression
	else if (expression->tag == unary_exp) {
		//recursively parse the child expression.
		ast* childExp = expression->op.unaryExp.operand;
		int child = eval(childExp, vars);
		//perform an operation.
		if (expression->op.unaryExp.operator == "-") {
			return child * -1;
		}
	}
	//integer
	else if (expression->tag == integer_exp) {
		return expression->op.integerExp;
	}
	//variable
	else if (expression->tag == variable_exp ) {
		gpointer* val = g_hash_table_lookup(vars, expression->op.variableExp);
		if (val != NULL) {
			return GPOINTER_TO_INT(val);
		}
	}

	//function
	else if ( expression->tag == function_exp ) {
		return eval(expression->op.functionExp.func, vars);
	}
}
