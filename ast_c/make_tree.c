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

		int varValue = eval(leftTree);
		printf("value: %i", varValue);

		g_hash_table_insert(hash, varName, GINT_TO_POINTER(varValue));
		ast* var = make_variableExp(varName);

		return var;

	}
	//case: operation
	if (tokens[0] == "*" || tokens[0] == "/" || tokens[0] == "+" || tokens[0] == "-") {

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