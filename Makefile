CC=gcc
FLAGS=-O2 -Wall -Wextra
D_FLAGS=-g -Wall -Wextra

ciobf: main.c fileio.c compile.c interpret.c options.c string_op.c
	$(CC) $(FLAGS) -o $@ $^ include/compile_info.h

debug: main.c fileio.c compile.c interpret.c options.c string_op.c
	$(CC) $(D_FLAGS) -o ciobf $^ include/compile_info.h

clean:
	rm ciobf
