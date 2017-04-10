The Abstract Syntax Tree and Parser create and parse syntax trees for basic arithmetic expressions. It is functional for additon, subtraction, multiplication and division, with positive and negative numbers. For example, 
```c
ast* additionexp = make_binaryExp("*", 
			make_binaryExp("+", 
				make_unaryExp("-", make_integerExp(5)), 
				make_integerExp(7)), 
			make_integerExp(20));
```
Represents the expression (-5 + 7) * 20, and 
```c
parser(additionexp)
```
will evaluate it to 40.

To use:

Run `make rdp`.