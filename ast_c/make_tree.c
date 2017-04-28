#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "ast.h"
#include "eval.h"

GHashTable* hash;

typedef struct node {
	struct node *next;
	char* key;
	ast* function;
} Node;

Node* head;
Node* tail;

Node* make_node(char* key, ast* function, Node* next) {
	Node* node = malloc(sizeof(node));
	node->key = key;
	node->function = function;
	node->next = next;
}

ast* make_tree(char* tokens[], int length) {

	//case: integer
	if (atoi(tokens[0]) != 0 || tokens[0] == "0") { 
		return make_integerExp(atoi(tokens[0]));
	} 
	//case: variable
	else if (g_hash_table_lookup(hash, tokens[0]) != NULL) {
		return make_variableExp(tokens[0]);
	}
	//case: variable definition
	else if (tokens[0] == "defvar") {
		printf("\n making a variable\n");

		char* varName = tokens[2];

		ast* leftTree;

		if (tokens[3] == "(") {
			char* nest[length-2];
			int numOpen = 1;
			int numClosed = 0;
			int i = 0; 

			while (numOpen > numClosed && i < length-3) { 
				nest[i] = tokens[i+4];
				printf("%s, ", nest[i]);
				if (nest[i] == "(") {
					numOpen += 1;
				} else if (nest[i] == ")") {
					numClosed += 1;
				}
				i++;
			}

			printf("\n----------\n");
			leftTree = make_tree(nest, i);
			printf("\n----------\n");
		}

		else {
			char* nest[] = {tokens[3]};
			leftTree = make_tree(nest, 1);
		}

		int varValue = eval(leftTree, hash);
		printf("value: %i", varValue);

		g_hash_table_insert(hash, varName, GINT_TO_POINTER(varValue));
		ast* var = make_variableExp(varName);

		return var;

	}

	//function definition
	else if (tokens[0] == "defun") {
		//I don't know how to do an arbitrary number of arguments. I'm just doing two for now.
		printf("creating function. \n");
		char* func_name = tokens[1];

		//extract variable names starting at tokens[3]
		char* arguments[length - 3];

		int numOpen = 1;
		int numClosed = 0;
		int i = 0;
		while (numOpen > numClosed) {
			arguments[i] = tokens[i+3];
			if (arguments[i] == "(") {
				numOpen += 1;
			} else if (arguments[i] == ")") {
				numClosed += 1;
			}
			i++;
		}

		int num_arguments = i-1;

		printf("function name: %s. arguments: ", func_name );

		for (int j = 0; j < i-1; j++ ) {
			char* arg = arguments[j];
			g_hash_table_insert(hash, arg, GINT_TO_POINTER(1));
			printf("%s, ", arg);
		}

		printf("\n");
		char* nest[length-5];
		numOpen = 1;
		numClosed = 0;
		i = 0;
		while (numOpen > numClosed && i < length - 6) {
			nest[i] = tokens[i+7];
			printf("%s, ", nest[i]);
			if (nest[i] == "(") {
				numOpen += 1;
			} else if (nest[i] == ")") {
				numClosed += 1;
			}
			i++;
		}

		printf("\n----------\n");
		ast* subtree = make_tree(nest, i);
		printf("\n----------\n");

		ast* tree = make_functionExp(func_name, subtree, num_arguments, arguments);

		Node* node = make_node(func_name, tree, NULL);
		if (head == NULL) {
			head = node;
		} 
		if (tail == NULL) {
			tail = node;
		} else {
			tail->next = node;
			tail = node;
		}

		return tree;
	}

	//case: operation
	else if (tokens[0] == "*" || tokens[0] == "/" || tokens[0] == "+" || tokens[0] == "-") {

		ast* leftTree;
		int rightIndex;

		//nested case
		if (tokens[1] == "(") {
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
			leftTree = make_tree(nest, i);
			printf("\n----------\n");
			printf("created left tree.\n");
			rightIndex = i+2;
		}
		//non-nested case
		else {
			char* nest[] = {tokens[1]};
			leftTree = make_tree(nest, 1);
			rightIndex = 2;
		}

		//shit's binary
		if (tokens[rightIndex] != ")") {
			printf("binary expression. attempting right tree starting at %i\n", rightIndex);

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
				rightTree = make_tree(nest, i);
				printf("\n----------\n");
				printf("created right tree. \n");

			} else {
				char* nest[] = {tokens[rightIndex]};
				rightTree = make_tree(nest, 1);
			}

			ast* retval = make_binaryExp(tokens[0], leftTree, rightTree);
			printf("made the tree\n");
			return retval;
		}

		//shit's unary
		else {
			printf("Found a unary expression");
			ast* retval = make_unaryExp(tokens[0], leftTree);
			return retval;
		}
	}

	else {
		//check if it's a function
		char* func_name = tokens[0];
		Node* current = head;
		while (current != NULL) {
			if (strcmp(current->key, func_name) == 0) {
				printf("found a function!\n");
				int num_arguments = current->function->op.functionExp.num_arguments;
				for (int i = 0; i < num_arguments; i++) {
					char* arg = current->function->op.functionExp.arguments[i];
					int val = atoi(tokens[i+1]); //simplifying to the easiest case. I'll come back to this.
					g_hash_table_insert(hash, arg, GINT_TO_POINTER(val)); //this should eventually go in a local variable space.
				}
				return current->function;
			}
		}

		printf("Not a valid symbol %s", tokens[0]);
		return NULL;
	}
}


int main() {
	//initialize global variables
	hash = g_hash_table_new(g_str_hash, g_str_equal); // a hashtable with strings as keys.

	char* functiontTokens[] = {"defun", "myfun", "(", "y", "z", ")", "(", "+", "y", "z", ")"};
	char* evalFunctionTokens[] = {"myfun", "5", "7"};
	ast* first_func = make_tree(functiontTokens, 11);
	ast* eval_func = make_tree(evalFunctionTokens, 3);
	int val = eval(eval_func, hash);

	printf("%i\n", val);

	char* tokens[] = {"*", "5", "7"};
	char* tokens2[] = { "+", "(", "*", "5", "x", ")", "9"}; // ( + ( * 5 x ) 9 ) = 5*10 + 9 = 59
	char* tokens3[] = {"+", "(", "*", "5", "(", "/", "6", "3", ")", ")", "9"}; //(+ ( * 5 ( / 6 3 ) ) 9 ) = 5*(-6) + 9 = 19
	char* tokens4[] = {"defvar", "(", "x", "(", "+", "7", "10", ")"};
	char* tokens5[] = {"defvar", "(", "x", "10", ")"};

	ast* tree1 = make_tree(tokens5, 5);

	ast* tree2 = make_tree(tokens2, 7);

	int answer = eval(tree2, hash);

	printf("answer: %i\n", answer);

	return 0;
}