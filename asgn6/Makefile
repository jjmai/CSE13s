CFLAGS = -Wpedantic -Werror -Wall -Wextra -std=c99
CC = clang $(CFLAGS)


all		:	newspeak

newspeak	:	newspeak.o bv.o bf.o gs.o hash.o ll.o parser.o speck.o
		$(CC) -o newspeak newspeak.o bv.o bf.o gs.o hash.o ll.o parser.o speck.o

newspeak.o	:	newspeak.c
		$(CC) -c newspeak.c

bv.o		:	bv.c
		$(CC) -c bv.c

bf.o		:	bf.c
		$(CC) -c bf.c

gs.o		:	gs.c
		$(CC) -c gs.c

hash.o		:	hash.c
		$(CC) -c hash.c

ll.o		:	ll.c
		$(CC) -c ll.c

parser.o	:	parser.c
		$(CC) -c parser.c

speck.o		:	speck.c
		$(CC) -c speck.c

clean		:
		rm -rf newspeak *.o infer-out

infer		:
		make clean; infer-capture -- make; infer-analyze -- make; 
