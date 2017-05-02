/* 
Code to build an abstract syntax tree, which is done recursively. 

To use, run:
$ make interpreter
$ ./interpreter <lisp file>

Lisp files can contain functions defined with defun, variables defined with defvar, and unary or binary arithmetic operations. 
Tokens in a lisp file should be separated by spaces for proper splitting. 

*/

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include "ast.h"
#include "eval.h"

/* A node of a linked list of functions.*/
typedef struct node {
	struct node *next;
	char* key;
	ast* function;
} Node;

GHashTable* hash;
Node* head;
Node* tail;

/* creates a function node and adds it to the linked list. */
Node* make_node(char* key, ast* function, Node* next) {
	Node* node = malloc(sizeof(node));
	node->next = next;
	node->key = key;
	node->function = function;
	return node;
}

/* Fills out a new subarray that contains a nested array in the outermost parentheses.
Returns the length of the subarray as an integer. */
int make_subarray(char* original[], char* nest[], int offset, int length) {
	int numOpen = 1;
	int numClosed = 0;
	int i = 0;
	while (numOpen > numClosed && i < length-offset+1){
		nest[i] = original[i+offset];
		if ( strcmp(nest[i], "(") == 0 ) {
			numOpen += 1;
		} else if (strcmp(nest[i], ")") == 0 ) {
			numClosed += 1;
		}
		i++;
	}
	return i;
}

/* Given a list of tokens and a length, creates an abstract syntax tree. */
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
		char* varName = tokens[2];
		ast* leftTree;
		if (strcmp(tokens[3], "(") == 0 ) {
			char* nest[length-2];
			int i = make_subarray(tokens, nest, 4, length);
			leftTree = make_tree(nest, i);
		}
		else {
			printf("integer input");
			char* nest[] = {tokens[3]};
			leftTree = make_tree(nest, 1);
		}
		int varValue = eval(leftTree, hash);
		g_hash_table_insert(hash, varName, GINT_TO_POINTER(varValue));
		ast* var = make_variableExp(varName);
		return var;

	}

	//function definition
	else if (strcmp(tokens[0],"defun") == 0 ) {
		char* func_name = malloc(sizeof(tokens[1]));
		strcpy(func_name, tokens[1]);
		char* arguments[length - 3]; //extract variable names starting at tokens[3]
		int numOpen = 1;
		int numClosed = 0;
		int i = 0;
		while (numOpen > numClosed) {
			char* arg = malloc(sizeof(tokens[i+3]));
			strcpy(arg, tokens[i+3]);
			arguments[i] = arg;
			if ( strcmp(arguments[i], "(") == 0 ) {
				numOpen += 1;
			} else if (strcmp(arguments[i], ")") == 0 ) {
				numClosed += 1;
			}
			i++;
		}
		int num_arguments = i-1;
		for (int j = 0; j < i-1; j++ ) {
			char* arg = arguments[j];
			g_hash_table_insert(hash, arg, GINT_TO_POINTER(1));
		}
		char* nest[length-5];
		i = make_subarray(tokens, nest, 5 + num_arguments, length);
		ast* subtree = make_tree(nest, i);
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
		return NULL;
	}

	//case: operation
	else if (strcmp(tokens[0], "*") == 0 || strcmp(tokens[0], "/") == 0|| strcmp(tokens[0], "+") == 0 || strcmp(tokens[0], "-") == 0 ) {
		ast* leftTree;
		int rightIndex;
		//nested case
		if ( strcmp(tokens[1],"(") == 0 ){
			char* nest[length-2];
			int i = make_subarray(tokens, nest, 2, length);
			leftTree = make_tree(nest, i);
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

			ast* rightTree;
			if ( strcmp(tokens[rightIndex],"(") == 0 ) { 
				char* nest[length-2];
				int i = make_subarray(tokens, nest, rightIndex+1, length);
				rightTree = make_tree(nest, i);
			} else {
				char* nest[] = {tokens[rightIndex]};
				rightTree = make_tree(nest, 1);
			}
			ast* retval = make_binaryExp(tokens[0], leftTree, rightTree);
			return retval;
		}

		//shit's unary
		else {
			ast* retval = make_unaryExp(tokens[0], leftTree);
			return retval;
		}
	//if statement
	} else if ( strcmp(tokens[0], "if") == 0 ) {
		int rightIndex;
		ast* leftTree;
		if (atoi(tokens[2]) != 0 || strcmp(tokens[2], "0") == 0 ) {
			rightIndex = 3;
			int val = atoi(tokens[2]);
			leftTree =  make_integerExp(val);
		} else if ( strcmp(tokens[2], "(") == 0 ) {
			char* nest[length-3];
			int i = make_subarray(tokens, nest, 3, length);
			rightIndex = i+3;
			leftTree = make_tree(nest, i);
		} else {
			perror("not a valid expression.");
			exit(-1);
		}


		//if true
		if ( strcmp(tokens[1], "t") == 0 ) {
			return leftTree;
		//if false
		} else if ( strcmp(tokens[1], "nil") == 0 ) {
			if ( atoi(tokens[rightIndex]) != 0 || strcmp(tokens[rightIndex], "0") == 0 ) {
				int val = atoi(tokens[rightIndex]);
				return make_integerExp(val);
			} else if ( strcmp(tokens[rightIndex], "(") == 0) {
				char* nest[length-rightIndex];
				int i = make_subarray(tokens, nest, rightIndex+1, length);
				ast* rightTree = make_tree(nest, i);
				return rightTree;
			} else {
				perror("not a valid expression");
				exit(-1);
			}
		} else {
		perror("not a valid boolean operator");
		exit(-1);
		}
	} else {
		//check if it's a function
		char* func_name = tokens[0];
		Node* current = head;
		while (current != NULL) {
			if ( strcmp(current->key, func_name) == 0) {
				int num_arguments = current->function->op.functionExp.num_arguments;
				int arg_num = 0; 
				int i  = 0;
				while ((arg_num < num_arguments) && (i < length)) {
					char* arg_original = current->function->op.functionExp.arguments[i];
					int val;
					if (atoi(tokens[i+1]) != 0 || strcmp(tokens[i+1], "0") == 0 ) {
						val = atoi(tokens[i+1]); 
						arg_num++;
						i++;
					} else {
						perror("not a valid input. ");
						exit(-1);
					}

					char* arg = malloc(sizeof(arg_original));
					strcpy(arg, arg_original);
					gpointer* val_pointer = GINT_TO_POINTER(val);
					g_hash_table_insert(hash, arg, val_pointer); //this should eventually go in a local variable space.
				}
				return current->function;
			}
			current = current->next;
		}
		printf("\nNot a valid symbol %s\n", tokens[0]);
		return NULL;

	}
}


/* Takes a lisp file name as input and parses stuff */
int main(int argc, char *argv[]) { 
	//initialize global variables
	hash = g_hash_table_new(g_str_hash, g_str_equal); // a hashtable with strings as keys.

	if (argc > 1) {

		printf("-----\nreading from lisp file.\n\n");

		FILE *f = fopen(argv[1], "r");

		for (;;) {
			char line[80];
			char *token;

			if (fgets(line, 80, f) == NULL) break;
			token = strtok(line, " ");

			char* tokens[20]; //I need to have some limit on how many symbols in a line, but this is arbitrary.
			int i = 0;
			while (token) {
				if (i != 0) {
					tokens[i-1] = token;
					printf("%s ", token);
				}
				token = strtok(NULL, " ");
				i++;
			}
			ast* tree = make_tree(tokens, i-1); //-1 to account for trailing parenthese.
			int val = eval(tree, hash);
			if (eval(tree, hash) != NULL) {
				printf("\nanswer: %i\n\n", val);
			} else {
				printf("\n\n");
			}
		}
		fclose(f);
	}
	return 0;
}