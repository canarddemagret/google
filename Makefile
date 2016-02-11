all:
	gcc -std=c99 main.c parser.c -lm

clean:
	rm -f *.o
	rm ./a.out
