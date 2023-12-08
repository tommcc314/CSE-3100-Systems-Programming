CC=cc
CFLAGS=-g

all: dltest

dltest: dllist.o dltest.o
	$(CC) $(CLFAGS) -o $@  $^

%.o : %.c dllist.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o dltest
