## A Basic Example
A rudimentary lex file that returns "GOODBYE" if you type "hello world"
### How to run:
	$ lex ex1.l
	$ cc lex.yy.c -ll
	$ ./a.out
	hello world
	GOODBYE

(ctrl+c to quit)

## A Less Basic Example
A tokenizer. More about tokenization [here](https://en.wikipedia.org/wiki/Tokenization_(lexical_analysis))

### How to run:
	$ lex myscanner.l
	$ cc myscanner.c lex.yy.c -o myscanner
	$ ./myscanner <config.in 
	1
	db_type is set to mysql
	2
	db_name is set to testdata
	3
	db_table_prefix is set to test_
	4
	db_port is set to 1099

### Files

**config.in**: names value pairs separated by a colon

**myscanner.l**: explanation of lex file: https://youtu.be/54bo1qaHAfk?t=16m29s 

**myscanner.c**: The c file that takes the config, lex, and c files to tokenize
