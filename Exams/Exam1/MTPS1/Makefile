CFLAGS=-g -std=c99
CC=cc

all: subsetsum

subsetsum: subsetsum.o subsetsumCode.o
	$(CC) $(CFLAGS) -o $@ $?

clean:
	rm -rf *.o subsetsum *.dSYM *~ _minted-mt1
