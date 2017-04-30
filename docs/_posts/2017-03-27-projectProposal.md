---
title: Project Proposal
layout: post
permalink: /projectProposal/
cover: cover.jpg
date:   2017-03-27 12:00:00
categories: posts
source-id: 1Y4fFW8D73ttbxVgCn96xcFKfG_tXMEALBgj7vx_yWCo
published: true
---
# Project Proposal - Eccentric Eucalyptus

#### 1) State the goal of your project, ideally including a lower bound you are confident you can achieve and a stretch goal that is more ambitious.

We are coding a language interpreter using C. Our goal is to solidify our skills in C and to learn more about programming languages. Our lower bound would be a lisp interpreter, and our upper bound would be a general language interpreter. If we pursue this upper bound, we will need to talk to Professor Pucella and learn how programming languages work.

#### 2) Demonstrate that you have acquired the knowledge you need to get started.  We will know that you have this knowledge if the text of the proposal uses domain language effectively to convey ideas clearly and concisely.

* We are going to read in a lisp file, build an abstract syntax tree, and then execute the syntax tree. One option for building the abstract syntax tree is to use a recursive descent parser.

* We also experimented with different C tools such as lex & yacc. We already coded a simple tokenizer that breaks up a stream of text into words.

* Our knowledge of RegEx may help us for parsing strings

#### 3) Demonstrate that you have assembled the resources you need to get started.  One good way to do that is to include an annotated bibliography with a pointer to each resource and a few sentences that describe the content.

* Purple Dragon Book(Compilers: Principles, Techniques, and Tools): book on programming languages, compilers, and computer architecture.

* Minimal set of primitives for lisp [FAQ](http://www.faqs.org/faqs/lisp-faq/part1/section-6.html) : Guide on basic lisp structures to implement

* Riccardo Pucella: Good at programming languages

* [Lex and Yacc](http://dinosaur.compilertools.net/): tools to help break down and parse programs

#### 4) Present a product backlog for the next two sprints that represents a concrete plan that will keep the entire team productively engaged (this can be a link to your Trello board).  Each item in the product backlog should represent a good sized unit of work, and have an appropriate definition of done.

* [Trello](https://trello.com/b/nbNxuLH8/softsyseccentriceucalyptus)

#### 5) Enumerate potential roadblocks and ways instructors can help.  Do you need materials?  Do you have show-stopping questions you have not been able to answer?

We think that some of the major hurdles we will face are understanding the theory behind programming languages and code structure. We are coming in without much domain knowledge about how programming languages work, so we will have to do a lot of learning in order to get something that works. This is also a project that could potentially be very large, with a lot of text parsing, so we will need to be very careful to make our code legible and modular.
