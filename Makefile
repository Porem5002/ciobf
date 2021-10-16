CC=gcc
FLAGS=-O2

ciobf: main.c fileio.c ciobf.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm ciobf
