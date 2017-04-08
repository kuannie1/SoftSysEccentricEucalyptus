#include <stdlib.h>
#include <stdio.h>
#include "ast.h"


int parser(ast* expression) {
	if (expression-> tag == binary_exp) {
		printf("it's a binary expression!\n");
		ast* leftExp = expression -> op.binaryExp.left;
		int leftside = parser(leftExp);
		ast* rightExp = expression-> op.binaryExp.right;
		int rightside = parser(rightExp);
		if (expression->op.binaryExp.operator == "+") {
			return rightside + leftside;
		}
	}
	else if (expression->tag == unary_exp) {
		printf("it's a unary expression!\n");
		ast* childExp = expression->op.unaryExp.operand;
		int child = parser(childExp);
		if (expression->op.unaryExp.operator == "-") {
			return child * -1;
		}
	}
	else if (expression->tag == integer_exp) {
		printf("it's an integer!\n");
		return expression->op.integerExp;
	}
}



int main() {
	
	ast* additionexp = make_binaryExp("+", make_unaryExp("-", make_integerExp(5)), make_integerExp(7));
	int retval = parser(additionexp);
	printf("%i\n", retval);
	return 0;
}
