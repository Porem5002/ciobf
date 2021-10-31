CC=gcc
FLAGS=-O2

ciobf: main.c fileio.c compile.c interpret.c options.c
	$(CC) $(FLAGS) -o $@ $^

debug: main.c fileio.c compile.c interpret.c options.c
	$(CC) $(FLAGS) -o ciobf $^

clean:
	rm ciobf
