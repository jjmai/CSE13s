CFLAGS = -Wpedantic -Werror -Wall -Wextra -std=c99 
CC = clang $(CFLAGS)
VFLAGS = --leak-check=full --show-leak-kinds=all -v

all		:	sorting

sorting		:	sorting.o bubble.o shell.o quick.o binary.o
		$(CC) -o sorting sorting.o bubble.o shell.o quick.o binary.o -lm

sorting.o	:	sorting.c bubble.c shell.c quick.c binary.c
		$(CC) -c sorting.c bubble.c shell.c quick.c binary.c

clean		:	
		rm -rf sorting sorting.o bubble.o shell.o quick.o binary.o infer-out

infer		:
		make clean; infer-capture -- make; infer-analyze -- make

valgrind	:
		make clean; valgrind $(VFLAGS) -- make
