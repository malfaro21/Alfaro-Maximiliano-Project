a.out : main.o
	gcc -o $@ main.o

main.o : main.c
	gcc -c $?