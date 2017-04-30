typedef struct Exp {

	enum { integer_exp, string_exp, variable_exp,
		binary_exp, unary_exp,
		function_exp } tag;

	union {
		int integerExp;
		char* stringExp;
		char* variableExp;
		//a binary operation (ike addition, subtraction, multiplication, division)
		struct {char* operator;
			struct Exp* left;
			struct Exp* right; } binaryExp;
		//a unary operation (like a negative sign)
		struct { char* operator;
			struct Exp* operand; } unaryExp;
		//function
		struct { char* name;
			struct Exp* func;
			int num_arguments;
			char* arguments[]; } functionExp;
	} op;

} ast;


ast *make_binaryExp ( char* operator, ast* left, ast* right );
ast *make_unaryExp( char* operator, ast* operand );
ast *make_integerExp( int integerExp );
ast* make_stringExp( char* stringExp );
ast* make_variableExp( char* variableExp );
ast* make_functionExp( char* name, ast* func, int num_arguments, char* arguments[] );