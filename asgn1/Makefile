CFLAGS = -Wpedantic -Werror -Wall -Wextra
CC=clang $(CFLAGS)

all:lrc

lrc	:	lrc.o
	$(CC) -o lrc lrc.o
lrc.o	:	lrc.c
	$(CC) -c lrc.c
clean	:
	rm -rf lrc lrc.o infer-out
infer	: clean
	infer-capture -- make
	infer-analyze -- make

