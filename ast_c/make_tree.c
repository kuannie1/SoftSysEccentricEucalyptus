#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "ast.h"
#include "eval.h"

GHashTable* hash; 
GHashTable* functions;

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

ast* make_tree(char* tokens[], int numtokens, int length) {

	//case: integer
	if (atoi(tokens[0]) != 0 || tokens[0] == "0") { 
		return make_integerExp(atoi(tokens[0]));
	} 
	//case: variable
	else if (g_hash_table_lookup(hash, tokens[0]) != NULL) {
		return make_variableExp(tokens[0]);
	}
	//case: variable definition
	else if (tokens[0] == "let") {
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
			leftTree = make_tree(nest, 3, i);
			printf("\n----------\n");
		}

		else {
			char* nest[] = {tokens[3]};
			leftTree = make_tree(nest, 3, 1);
		}

		int varValue = eval(leftTree, hash);
		printf("value: %i", varValue);

		g_hash_table_insert(hash, varName, GINT_TO_POINTER(varValue));
		ast* var = make_variableExp(varName);

		return var;

	}

	//lambda function definition
	else if (tokens[0] == "lambda") {
		//I don't know how to do an arbitrary number of arguments. I'm just doing two for now.
		printf("creating lambda function. \n");
		char* func_name = tokens[1];
		char* arg1 = tokens[3];
		char* arg2 = tokens[4];

		printf("function name: %s. arguments: %s, %s.\n", func_name, arg1, arg2);

		//jank ass way of dealing with things. Everything is in the same variable space. 
		g_hash_table_insert(hash, arg1, GINT_TO_POINTER(1));
		g_hash_table_insert(hash, arg2, GINT_TO_POINTER(1));

		char* nest[length-5];
		int numOpen = 1;
		int numClosed = 0;
		int i = 0;
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
		ast* tree = make_tree(nest, 3, i);
		printf("\n----------\n");

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
			leftTree = make_tree(nest, 3, i);
			printf("\n----------\n");
			printf("created left tree.\n");
			rightIndex = i+2;
		}
		//non-nested case
		else {
			char* nest[] = {tokens[1]};
			leftTree = make_tree(nest, 3, 1);
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
				rightTree = make_tree(nest, 3, i);
				printf("\n----------\n");
				printf("created right tree. \n");

			} else {
				char* nest[] = {tokens[rightIndex]};
				rightTree = make_tree(nest, 3, 1);
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
		printf("Not a valid symbol %s", tokens[0]);
		return NULL;
	}
}


int main() {
	//initialize global variables
	hash = g_hash_table_new(g_str_hash, g_str_equal); // a hashtable with strings as keys.
	char* firstTokens[] = {"lambda", "myfun", "(", "y", "z", ")", "(", "+", "y", "z", ")"};
	ast* first_func = make_tree(firstTokens, 3, 11);
	Node* node = make_node(NULL, first_func, NULL);
	head = node;
	tail = node;

	char* tokens[] = {"*", "5", "7"};
	char* tokens2[] = { "+", "(", "*", "5", "x", ")", "9"}; // ( + ( * 5 x ) 9 ) = 5*10 + 9 = 59
	char* tokens3[] = {"+", "(", "*", "5", "(", "/", "6", "3", ")", ")", "9"}; //(+ ( * 5 ( / 6 3 ) ) 9 ) = 5*(-6) + 9 = 19
	char* tokens4[] = {"let", "(", "x", "(", "+", "7", "10", ")"};
	char* tokens5[] = {"let", "(", "x", "10", ")"};

	ast* tree1 = make_tree(tokens5, 3, 5);

	ast* tree2 = make_tree(tokens2, 3, 7);

	int answer = eval(tree2, hash);

	printf("answer: %i\n", answer);

	functions = g_hash_table_new(g_str_hash, g_str_equal);

	return 0;
}