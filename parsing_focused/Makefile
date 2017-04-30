ast.o: ast.c ast.h
	gcc -c ast.c

eval.o: eval.c eval.h
	gcc -c eval.c `pkg-config --cflags --libs glib-2.0`

interpreter: ast.o eval.o interpreter.c
	gcc -g ast.o eval.o interpreter.c -o interpreter `pkg-config --cflags --libs glib-2.0`


