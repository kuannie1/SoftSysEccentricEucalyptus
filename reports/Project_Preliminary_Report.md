---
title: Project Preliminary Report
layout: post
author: hooticambo
permalink: /project-preliminary-report/
source-id: 1q7iQMmCzHjGNeVvEQ436JXu3gx5GZUCc9ouAwWzknm8
published: true
---
# Eccentric Eucalyptus - LISP Interpreter

Anne Ku, Margaret Crawford, Nathan Yee, Serena Chen

## Project Goals

We are coding a language interpreter using C. Our goal is to solidify our skills in C and to learn more about programming languages. Our lower bound would be a lisp interpreter, and our upper bound would be an interpreter that can parse user-generated structs in the language of our choice.

We also identified some learning goals in our team that may shape how we approach this project. Our learning goals include gaining an understanding of how programming languages are implemented at a low level, and understanding parsing of not only programming languages, but a wide variety of files (such as markup language files). We're hoping that our conversation with Riccardo Pucella (this Thursday) will help us better understand what to do and how we our project can best fit our goals.

## Trello Card Progress

* Project Proposal

    * Did the project proposal with the team.

* Read resources on abstract syntax tree in C

    * [https://lambda.uta.edu/cse5317/notes/node26.html](https://lambda.uta.edu/cse5317/notes/node26.html)

    * [http://stackoverflow.com/questions/21150454/representing-an-abstract-syntax-tree-in-c](http://stackoverflow.com/questions/21150454/representing-an-abstract-syntax-tree-in-c)

* watch intro to yacc video

    * Watched the intro video to yacc.

    * Also watched the continuation videos

* Learn basic lisp syntax - printing calculator operations

    * Learned calculator syntax using an online lisp interpreter

* Implement lisp like calculator using yacc

    * Made a lisp like calculator that uses yacc to define the grammatical rules for basic expressions such as multiplication, division, addition, subtraction.

* implement the structs version of the abstract syntax tree

    * [https://github.com/kuannie1/SoftSysEccentricEucalyptus/tree/master/ast_c](https://github.com/kuannie1/SoftSysEccentricEucalyptus/tree/master/ast_c)

* Read Over Chp. 2 of Purple Dragon Book

    * Attempted to read the second chapter of the purple dragon book. 

## Preliminary Progress - Code

We made README.md files that explain each portion of our progress:

* [Calculator](https://github.com/kuannie1/SoftSysEccentricEucalyptus/blob/master/calculator/prefix_calculator/prefix_calculator.md)

* [Abstract Syntax Tree](https://github.com/kuannie1/SoftSysEccentricEucalyptus/tree/master/ast_c)

* [Tokenizer](https://github.com/kuannie1/SoftSysEccentricEucalyptus/tree/master/lex_examples)

## Resources

Our resources have not changed since the beginning of this project. 

* Purple Dragon Book(Compilers: Principles, Techniques, and Tools): book on programming languages, compilers, and computer architecture. 

* Minimal set of primitives for lisp [FAQ](http://www.faqs.org/faqs/lisp-faq/part1/section-6.html) : Guide on basic lisp structures to implement

* Riccardo Pucella: Good at programming languages

* [Lex and Yacc](http://dinosaur.compilertools.net/): tools to help break down and parse programs

## Backlog

This is the backlog that will guide us to combining our knowledge and creating our lisp interpreter.

* Taking tokens and putting them into the Abstract Syntax Tree

* Combining the lexer and parser

* Making a function that returns the next token from the lexer

* Incorporating variable assignment and functions

* Representing variables and functions in the Abstract Syntax Tree

## Potential Roadblocks

We're still struggling with structuring our code and combining our work in a meaningful way. This is an interesting project with a lot of text parsing, so we will need to be very careful to make our code legible and modular. We also found many different solutions for implementing parts of an interpreter (like using yacc and abstract syntax trees to create a calculator), and no solutions for implementing other parts (like defining functions or going from tokenizing to parsing), so the way forward is not very clear. We hope to set up a meeting with Riccardo to understand the processes we are confused about and gain more insight on the different ways to implement our interpreter so we can feel a little less jumbled.

