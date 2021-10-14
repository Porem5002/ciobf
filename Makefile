CC=gcc
FLAGS=-O2

ciobf: main.c fileio.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm ciobf
