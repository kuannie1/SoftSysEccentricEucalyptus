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
	if (atoi(tokens[0]) != 0 || strcmp(tokens[0], "0") == 0 ) {
		return make_integerExp(atoi(tokens[0]));
	} 
	//case: variable
	else if (g_hash_table_lookup(hash, tokens[0]) != NULL) {
		return make_variableExp(tokens[0]);
	}
	//case: variable definition
	else if (strcmp(tokens[0],"defvar") == 0 ) {
		printf("\n making a variable\n");

		char* varName = tokens[2];

		ast* leftTree;

		if (strcmp(tokens[3], "(") == 0 ) {
			char* nest[length-2];
			int numOpen = 1;
			int numClosed = 0;
			int i = 0; 

			while (numOpen > numClosed && i < length-3) { 
				nest[i] = tokens[i+4];
				printf("%s, ", nest[i]);
				if ( strcmp(nest[i], "(") == 0 ) {
					numOpen += 1;
				} else if (strcmp(nest[i], ")") == 0 ) {
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
	else if (strcmp(tokens[0],"defun") == 0 ) {
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
			if ( strcmp(arguments[i], "(") == 0 ) {
				numOpen += 1;
			} else if (strcmp(arguments[i], ")") == 0 ) {
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

		printf(" ( %i arguments total ).\nfunction body: ", num_arguments);
		char* nest[length-5];
		numOpen = 1;
		numClosed = 0;
		i = 0;
		while (numOpen > numClosed && i < length - 6) {
			nest[i] = tokens[i+num_arguments+5];
			printf("%s, ", nest[i]);
			if ( strcmp(nest[i], "(") == 0 ) {
				numOpen += 1;
			} else if (strcmp(nest[i], ")") == 0 ) {
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
			printf("assigning head to %s\n", func_name);
			head = node;
		} 
		if (tail == NULL) {
			printf("assigning tail to %s\n", func_name);
			tail = node;
		} else {
			tail->next = node;
			tail = node;
		}

		return tree;
	}

	//case: operation
	else if (strcmp(tokens[0], "*") == 0 || strcmp(tokens[0], "/") == 0|| strcmp(tokens[0], "+") == 0 || strcmp(tokens[0], "-") == 0 ) {

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
				if ( strcmp(nest[i], "(") == 0 ) {
					numOpen += 1;
				} else if (strcmp(nest[i], ")") == 0 ) {
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
		if ( strcmp(tokens[rightIndex], ")") != 0 ) {
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
					if ( strcmp(nest[i], "(") == 0 ) {
					numOpen += 1;
					} else if (strcmp(nest[i], ")") == 0 ) {
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
		printf("checking if it's in the function list. \n");
		char* func_name = tokens[0];
		Node* current = head;
		while (current != NULL) {
			if (strcmp(current->key, func_name) == 0) {
				printf("found a function named %s!\n", current->key);
				int num_arguments = current->function->op.functionExp.num_arguments;

				for (int i = 0; i < num_arguments; i++) {
					char* arg = current->function->op.functionExp.arguments[i];
					int val = atoi(tokens[i+1]); //simplifying to the easiest case. I'll come back to this.
					printf("%s: %i, ", arg, val);
					g_hash_table_insert(hash, arg, GINT_TO_POINTER(val)); //this should eventually go in a local variable space.
				}
				return current->function;
			}

			current = current->next;
		}

		printf("Not a valid symbol %s\n", tokens[0]);
		return NULL;
	}
}

/* Takes a lisp file name as input and parses stuff */
int main(int argc, char *argv[]) { 
	//initialize global variables
	hash = g_hash_table_new(g_str_hash, g_str_equal); // a hashtable with strings as keys.

	// char* functiontTokens[] = {"defun", "myfun", "(", "a", "b", "c", ")", "(", "+", "a", "b", ")"};
	// char* evalFunctionTokens[] = {"myfun", "5", "7", "9"};
	// ast* first_func = make_tree(functiontTokens, 12);
	// ast* eval_func = make_tree(evalFunctionTokens, 4);
	// int val = eval(eval_func, hash);

	// printf("%i\n", val);

	// char* tokens1[] = {"*", "5", "7"};
	// char* tokens2[] = { "+", "(", "*", "5", "x", ")", "9"}; // ( + ( * 5 x ) 9 ) = 5*10 + 9 = 59
	// char* tokens3[] = {"+", "(", "*", "5", "(", "/", "6", "3", ")", ")", "9"}; //(+ ( * 5 ( / 6 3 ) ) 9 ) = 5*(-6) + 9 = 19
	// char* tokens4[] = {"defvar", "(", "x", "(", "+", "7", "10", ")"};
	// char* tokens5[] = {"defvar", "(", "x", "10", ")"};

	// ast* tree1 = make_tree(tokens5, 5);

	// ast* tree2 = make_tree(tokens2, 7);

	// int answer = eval(tree2, hash);

	// printf("answer: %i\n", answer);

	if (argc > 1) {

		printf("-----\nreading from lisp file.\n");

		FILE *f = fopen(argv[1], "r");

		for (;;) {
			char line[80];
			char *token;

			if (fgets(line, 80, f) == NULL) break;
			token = strtok(line, " ");

			char* tokens[20]; //I need to have some limit on how many symbols in a line, but this is arbitrary.
			int i = 0;
			while (token) {
				printf("%s ", token);
				if (i != 0) {
					tokens[i-1] = token;
				}
				token = strtok(NULL, " ");
				i++;
			}
			printf("lets make a tree!\n");
			ast* tree = make_tree(tokens, i-1); //-1 to account for trailing parenthese.
			int val = eval(tree, hash);
			printf("\nanswer: %i\n\n", val);
		}
		fclose(f);
	}

	return 0;
}