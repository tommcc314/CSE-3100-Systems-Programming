CC=cc
CFLAGS=-g

all: matrix

matrix: matrix.o main.o
	$(CC) $(CFLAGS) -o $@ $^ -lrt -lpthread -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf *.o matrix *~
