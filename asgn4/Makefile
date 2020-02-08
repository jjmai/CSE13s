CFLAGS = Wpedantic -Werror -Wall -Wextra
CC=clang $(CFLASGS)

all		: sequence

sequence	: sequence.o sieve.o
		$(CC) -o sequence sequence.o sieve.o bv.o -lm

sequence.o	: sequence.c sieve.c bv.c sieve.h bv.h
		$(CC) -c sequence.c sieve.c bv.c 

sieve.o		: sieve.c bv.h sieve.h
		$(CC) -c sieve.c 

bv.o		: bv.c bv.h
		$(CC) -c bv.c 

clean		:
		rm -rf sequence sequence.o bv.o sieve.o infer-out	
