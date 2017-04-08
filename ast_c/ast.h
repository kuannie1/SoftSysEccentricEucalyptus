typedef struct Exp {

	enum { integer_exp, string_exp, variable_exp,
		binary_exp, unary_exp, call_exp,
		projection_exp, record_exp } tag;

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
		//a call operation (like a function???)
		struct { char* name;
			struct Exp_list* arguments; } callExp;
		//projection operation (still trying to figure out what this means)
		struct {struct Exp* record;
			char* attribute; } projectionExp;
		//also not sure what this is
		struct rec { char* attribute;
			struct Exp* value;
			struct rec* next; } recordExp;
	} op;

} ast;

typedef struct Exp_list { 
  ast*             elem;
  struct Exp_list* next;
} ast_list;

ast *make_binaryExp ( char* operator, ast* left, ast* right );
ast *make_unaryExp( char* operator, ast* operand );
ast *make_integerExp( int integerExp );
ast* make_stringExp( char* stringExp );
ast* make_variableExp( char* variableExp );
ast* make_callExp( char* name, ast_list* arguments );
ast* make_projectionExp( ast* record, char* attribute );
ast* make_recordExp( char* attribute, ast* value, struct rec* next );