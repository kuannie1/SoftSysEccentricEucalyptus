/*
A recursive descent parser implementation in C, using the ast struct by Leonidas Farigas. 
Currently supports: addition, subtraction, multiplication, divition, negative numbers. 
By Margo Crawford.
*/
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"


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
}



int main() {

	//(-5+7) * 20
	ast* additionexp = make_binaryExp("*", make_binaryExp("+", make_unaryExp("-", make_integerExp(5)), make_integerExp(7)), make_integerExp(20));
	int retval = parser(additionexp);
	printf("%i\n", retval);
	return 0;
}
