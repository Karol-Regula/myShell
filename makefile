compile: main.c shellFnc.c shellFnc.h
	gcc main.c shellFnc.c -o myShell

run: compile
	./myShell

clean:
	rm myShell
	rm *~
