CC=gcc
FLAGS=-O2
DFLAGS=-g

ciobf: main.c fileio.c ciobf.c options.c
	$(CC) $(FLAGS) -o $@ $^

debug: main.c fileio.c ciobf.c options.c
	$(CC) $(DFLAGS) -o $@ $^


clean:
	rm ciobf
