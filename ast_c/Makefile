ast.o: ast.c ast.h
	gcc -c ast.c

eval: ast.o eval.c
	gcc -g ast.o eval.c -o eval `pkg-config --cflags --libs glib-2.0`