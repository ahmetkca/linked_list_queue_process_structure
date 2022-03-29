all:
	gcc -Wall -g3 -fsanitize=address -o main main.c

clean:
	rm -f main