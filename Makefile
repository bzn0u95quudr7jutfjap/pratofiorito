
a.out:main.c
	clang -lcurses main.c

run: a.out
	./a.out

runclean: run
	rm ./a.out
