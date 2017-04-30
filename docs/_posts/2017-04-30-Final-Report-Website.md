---
title: Final Report Website
layout: post
permalink: /final-report-website/
cover: cover.jpg
date:   2017-04-30 12:00:00
categories: posts
source-id: 1oKZ7hCTr_D9rOoWEyee8ANtBtfWQYGjwUxBCEpMIeyQ
published: true
---
# **Goal and Background**

Our goal is to write an interpreter in C. Our personal learning goals included gaining an understanding of how programming languages are implemented at a low level, and understanding how to parse not only programming languages, but a wide variety of files (such as markup language files). We chose to interpret Lisp, since its syntax, with its heavy reliance on parentheses, facilitated a more straightforward implementation of the parser. By the end, of the project, we had hoped to implement basic numeric operations, functions, and variables, in order to understand parsing and the how the basic building blocks of programming languages worked.

Since we wanted gain a deeper understanding of parsing and interpreting programming languages, we split up and implemented two different versions of parsing and interpreting. The first version we have is included within the src directory, and includes heavy use of Yacc and Lex to assist with parsing. This version was significantly assisted by Riccardo Pucella, visiting lecturer at Olin. Our conversations with him guided much of the structure we used in the parsing and the interpreter. The other version is included in the directory ast_c. This version was less guided by the help of Dr. Pucella, but used Peter Norvig's *Lispy *interpreter, a Lisp interpreter written in Python, as a reference. This version served more as an exploration into how to build an abstract syntax tree and interpret it.

# **Lisp Interpreter -  Lex and Yacc based**

We made an interpreter that evaluates the contents of a lisp file with an open-source yacc parser generator called Bison. This interpreter supports function definitions through defun, variable definitions through let, and mathematical binary expressions. This portion of the project explores the use of parser generators and lexical tools to construct and evaluate abstract syntax trees. Dr. Pucella guided us throughout this portion with explaining how lisp files are deconstructed and visualized. 

Sample Input and Output:

Known limitations:

* Functions are restricted to one parameter and only one parameter (no parameter-less functions)

* No documentation in functions

* Different functions must have different parameter names, or else the name space is 

# **Lisp Interpreter - Parsing focused**

We made a lisp interpreter using only C, with no external libraries such as lisp or yacc. It recursively builds an abstract syntax tree, then evaluates it. It supports function definitions through defun and variable definitions through defvar, and unary and binary expressions. It reads from a lisp file, then builds a tree and evaluates it. Since our focus for this part was not on the syntax tree itself, but on creating it, much of the code for the tree was borrowed from Leonidas Ferigas. However, the code that builds the tree from an input file was purely written by us.

Sample input and output: 

<table>
  <tr>
    <td>( defun func2 ( a b c ) ( + a b ) )  
( func2 5 7 9 )</td>
    <td></td>
    <td>answer: 12</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td></td>
  </tr>
</table>


( * 5 7 )

answer: 35

( defvar ( x ( + 7 10 ) ) )

	answer: 17

( * 2 x )

answer: 34

( * ( + 7 ( - 9 3 ) ) 15 )

answer: 195

( defun func3 ( ) ( 18 ) )

( func3 )

	answer: 18

Known limitations:

* inputs to functions cannot be non-integers

* No support for local variables (including in function arguments)

* Finding a user defined function takes linear time with the number of functions that exist

* Every token must have white spaces between it, including nested parentheses

**Authors**

[Annie Ku](https://github.com/kuannie1), [Margo Crawford](https://github.com/Margaretmcrawf), [Nathan Yee](https://github.com/NathanYee), [Serena Chen](https://github.com/poosomooso)

# **Getting Started**

1. Install git and type this in the command line 

`git clone https://github.com/kuannie1/SoftSysEccentricEucalyptus.git`

## Additional step for using the lex and yacc based interpreter 

1. Install Bison by typing this in the command line

`sudo apt-get install flex bison`

# **Usage**

## Using the Lex and Yacc-based interpreter

`cd SoftSysEccentricEucalyptus/src`

`Make interpreter`

`./interpreter test.lisp`

## Using the parsing focused interpreter

`cd SoftSysEccentricEucalyptus/ast_c`

`make interpreter`

`./interpreter sample.lisp`

**Results**

