ast.o: ast.c ast.h
	gcc -c ast.c

eval.o: eval.c eval.h
	gcc -c eval.c `pkg-config --cflags --libs glib-2.0`

make_tree: ast.o eval.o make_tree.c
	gcc ast.o eval.o make_tree.c -o make_tree `pkg-config --cflags --libs glib-2.0`


