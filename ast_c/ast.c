/* 
Abstract Syntax Tree implementation in C, from Leonidas Ferigas.
https://lambda.uta.edu/cse5317/notes/node23.html
*/
int main() {
typedef struct Exp {

	enum { integer_exp, string_exp, variable_exp,
		binary_exp, unary_exp, call_exp,
		projection_exp, record_exp } tag;

	union {
		int integerExp;
		char* stringExp;
		char* variableExp;
		struct {char* operator;
			struct Exp* left;
			struct Exp* right; } binaryExp;
		struct { char* operator;
			struct Exp* operand; } unaryExp;
		struct { char* name;
			struct Exp_list* arguments; } callExp;
		struct {struct Exp* record;
			char* attribute; } projectionExp;
		struct rec { char* attribute;
			struct Exp* value;
			struct rec* next; } recordExp;
	} op;

} ast;

typedef struct Exp_list { 
  ast*             elem;
  struct Exp_list* next;
} ast_list;

return 0;
}