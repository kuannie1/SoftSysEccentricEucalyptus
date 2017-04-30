#!/bin/bash
# this script removes all executables, so that they
# don't interfere with compilation. Not necessary
# when using `make interpreter`.
rm lex.yy.c
rm parser
rm y.tab.c
rm y.tab.h
rm interpreter