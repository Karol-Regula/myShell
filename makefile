compile: main.c #list.c list.h songLib.c songLib.h
	gcc main.c -o myShell #songLib.c list.c

run: compile
	./myShell

clean:
	rm myShell
	rm *~
