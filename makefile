compile: main.c shellFnc.c shellFnc.h parse.c parse.h
	gcc main.c shellFnc.c parse.c -o myShell

run: compile
	./myShell

clean:
	rm myShell
	rm *~
