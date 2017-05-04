The parsing focused interpreter is a Lisp interpreter written in C, with no external libraries such as lisp or yacc. It recursively builds an abstract syntax tree, then evaluates it. It supports function definitions through defun and variable definitions through defvar, if statements with comparisons, and unary and binary expressions. It reads from a lisp file, then builds a tree and evaluates it. Since our focus for this part was not on the syntax tree itself, but on creating it, much of the code for the tree was borrowed from Leonidas Ferigas. However, the code that builds the tree from an input file was purely written by us.

To run:
```
$ make interpreter
$ ./interpreter <lisp_file>
```
sample.lisp contains some sample expressions for testing: 
```lisp
( defun func2 ( a b c ) ( + a b ) )
( func2 5 7 9 )
( * 5 7 )
( defvar ( x ( + 7 10 ) ) )
( * 2 x )
( * ( + 7 ( - 9 3 ) ) 15 )
( defun func3 ( ) ( 18 ) )
( func3 )
( defun func4 ( g h i ) ( * ( * g h ) i ) )
( func4 3 4 5 )
( if t 4 5 )
( if nil 4 5 )
( if ( > 5 7 ) 5 7 )
( if ( <= 1 3 ) ( + 8 1 ) 5 )
( if ( > ( + 1 7 ) ( - 8 1 ) ) 1 0 )
```
