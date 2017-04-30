# eLISP-Cs...

## Description
This repository contains two different implementations for a Lisp interpreter in C.
The first version we have is included within the `src` directory, and includes
heavy use of Yacc and Lex to assist with parsing. This version was significantly
assisted by Riccardo Pucella, visiting lecturer at Olin. Our conversations with
him guided much of the structure we used in the parsing and the interpreter.
The other version is included in the directory `ast_c`. This version was less guided
by the help of Dr. Pucella, but used
[Peter Norvig’s Lispy interpreter](http://norvig.com/lispy.html), a Lisp
interpreter written in Python, as a reference. This version served more as an
exploration into how to build an abstract syntax tree and interpret it.


## Authors
[Annie Ku](https://github.com/kuannie1)

[Margo Crawford](https://github.com/Margaretmcrawf)

[Nathan Yee](https://github.com/NathanYee)

[Serena Chen](https://github.com/poosomooso)

## Getting Started
```bash
git clone https://github.com/kuannie1/SoftSysEccentricEucalyptus.git
sudo apt-get install flex bison
```

## Usage
### Using the Lex and Yacc based interpreter
```bash
cd SoftSysEccentricEucalyptus/src
make interpreter
./interpreter <lisp file>
```
There is a test lisp file included in the directory, called `test.lisp`.
### Using the parsing focused interpreter
```bash
cd SoftSysEccentricEucalyptus/ast_c
make interpreter
./interpreter <lisp file>
```
There is a test lisp file included in the directory, called `sample.lisp`.

## License
The MIT License (MIT)
Copyright (c) 2013-2014 Jeff Martin
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
