
a.out:main.c
	clang -lcurses main.c

run: a.out
	./a.out

clean: run
	rm ./a.out
