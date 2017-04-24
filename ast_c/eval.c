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

int eval(ast* expression) {
	//binary expression
	if (expression-> tag == binary_exp) {
		//recursively parse the left and right expressions.
		ast* leftExp = expression -> op.binaryExp.left;
		int leftside = eval(leftExp);
		ast* rightExp = expression-> op.binaryExp.right;
		int rightside = eval(rightExp);
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
		int child = eval(childExp);
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

ast* make_tree(char* tokens[], int numtokens, int length) {

	if (numtokens == 2) {
		//shits unary
	}

	if (numtokens == 3) {
		//shits binary
		if (tokens[0] == "*" || tokens[0] == "/" || tokens[0] == "+" || tokens[0] == "-") {

			ast* leftTree;
			int rightIndex;

			if (tokens[1] == "(") { //youve got a nested tree to evaluate.

				printf("nested expression to evaluate\n");
				char* nest[length-2];
				int numOpen = 1;
				int numClosed = 0;
				int i = 0; //i is the index in the nested list, the index in the regular list is +2
				while (numOpen > numClosed && i < length-2) { //currently just assuming this will be passed something syntactically correct lol
					nest[i] = tokens[i+2];
					printf("%s, ", nest[i]);
					if (nest[i] == "(") {
						numOpen += 1;
					} else if (nest[i] == ")") {
						numClosed += 1;
					}
					i++;
				}

				printf("\n----------\n");
				leftTree = make_tree(nest, 3, i);
				printf("\n----------\n");
				printf("created left tree.\n");
				rightIndex = i+2;

			} else if (atoi(tokens[1]) != 0 || tokens[1] == "0") { //First argument is an integer. This is hella unsafe right now, because it doesn't distinguish between error and a value of zero.
				leftTree = make_integerExp(atoi(tokens[1]));
				rightIndex = 2;
				printf("found an integer as left tree\n");
			} else if (g_hash_table_lookup(hash, tokens[1]) != NULL) {
				leftTree = make_variableExp(tokens[1]);
				rightIndex = 2;
			} else {
				printf("Not a valid symblol %s", tokens[1]);
			}

			printf("attempting right tree starting at %i\n", rightIndex);

			ast* rightTree;
			if (tokens[rightIndex] == "(") { 
				printf("nested expression to evaluate\n");

				char* nest[length-2];
				int numOpen = 1;
				int numClosed = 0;
				int i = 0; //i is the index in the nested list, the index in the regular list is +2
				while (numOpen > numClosed && i < length-2) { //currently just assuming this will be passed something syntactically correct lol
					nest[i] = tokens[i+rightIndex + 1];
					printf("%s, ", nest[i]);
					if (nest[i] == "(") {
						numOpen += 1;
					} else if (nest[i] == ")") {
						numClosed += 1;
					}
					i++;
				}

				printf("\n----------\n");
				rightTree = make_tree(nest, 3, i);
				printf("\n----------\n");
				printf("created right tree. \n");


			} else if (atoi(tokens[rightIndex]) != 0 || tokens[rightIndex] == "0") { 
				rightTree = make_integerExp(atoi(tokens[rightIndex]));
				printf("found an integer as right tree\n");
			} else if (g_hash_table_lookup(hash, tokens[rightIndex]) != NULL) {
				rightTree = make_variableExp(tokens[rightIndex]);
			} else {
				printf("Not a valid symbol %s", tokens[rightIndex]);
			}

			ast* retval = make_binaryExp(tokens[0], leftTree, rightTree);
			printf("made the tree\n");
			return retval;
		}
	}
}

int main() {

	char* tokens[] = {"*", "5", "7"};
	char* tokens2[] = { "+", "(", "*", "5", "7", ")", "9"}; // ( + ( * 5 7 ) 9 ) = 5*7 + 9 = 44
	char* tokens3[] = {"+", "(", "*", "5", "(", "+", "6", "3", ")", ")", "9"}; //(+ ( * 5 ( + 6 3 ) ) 9 ) = 5*(6+3) + 9 = 54

	hash = g_hash_table_new(g_str_hash, g_str_equal); //a hashtable with strings as keys.

	ast* variable = make_variableExp("x");
	g_hash_table_insert(hash, "x", GINT_TO_POINTER(6));

	ast* tree = make_tree(tokens3, 3, 11);

	int answer = eval(tree);
	printf("%i\n", answer);

	//x = 6
	//(-5+7) * x
	ast* additionexp = make_binaryExp("*", make_binaryExp("+", make_unaryExp("-", make_integerExp(5)), make_integerExp(7)), variable);
	int retval = eval(additionexp);
	// printf("%i\n", retval);
	return 0;
}
