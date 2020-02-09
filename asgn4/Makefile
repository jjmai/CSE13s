CFLAGS = Wpedantic -Werror -Wall -Wextra
CC=clang $(CFLASGS)

all		: sequence

sequence	: sequence.o sieve.o
		$(CC) -o sequence sequence.o sieve.o bv.o -lm

sequence.o	: sequence.c sieve.c bv.c 
		$(CC) -c sequence.c sieve.c bv.c 

sieve.o		: sieve.c 
		$(CC) -c sieve.c 

bv.o		: bv.c 
		$(CC) -c bv.c 

clean		:
		rm -rf sequence sequence.o bv.o sieve.o infer-out

infer		:
		make clean; infer-capture -- make; infer-analyze -- make	
