
CLFAGS = -Wpedantic -Werror -Wall -Wextra
CC=clang $(CFLAGS)

all		: pathfinder

pathfinder	:	pathfinder.o stack.o
		$(CC) -o pathfinder pathfinder.o stack.o
pathfinder.o	:	pathfinder.c stack.c
		$(CC) -c pathfinder.c stack.c
stack		:	stack.o
		$(CC) -o stack stack.o
stack.o		:	stack.c
		$(CC) -c stack.c

clean		:
		rm -rf pathfinder pathfinder.o stack.o infer-out
infer		:
		make clean; infer-capture -- make; infer-analyze -- make
