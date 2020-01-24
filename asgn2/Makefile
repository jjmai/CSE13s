CFLAGS = -Wpedantic -Werror -Wall -Wextra
CC=clang $(CFLAGS)

all : math

math	:	math.o 
	$(CC) -o math math.o -lm
math.o	:	math.c 
	$(CC) -c math.c 
clean	:
	rm -rf math math.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make



