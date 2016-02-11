all:
	gcc -std=c99 main.c parser.c

clean:
	rm -f *.o
	rm ./a.out
