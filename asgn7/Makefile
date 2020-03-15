CFLAGS = -Wpedantic -Werror -Wall -Wextra -std=c99
CC = clang $(CFLAGS)

all		:	encode decode

encode		:	encode.o trie.o io.o
		$(CC) -o encode encode.o trie.o io.o -lm -g

decode		:	decode.o word.o io.o
		$(CC) -o decode decode.o word.o io.o -lm -g

encode.o	:	encode.c
		$(CC) -c encode.c

decode.o	:	decode.c
		$(CC) -c decode.c

trie.o		:	trie.c
		$(CC) -c trie.c

word.o		:	word.c
		$(CC) -c word.c

io.o		:	io.c
		$(CC) -c io.c

clean		:	
		rm -rf *.o encode decode
