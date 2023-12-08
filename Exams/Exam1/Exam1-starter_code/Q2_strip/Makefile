all: striptest

striptest : striptest.o strip.o
	cc -g -o $@ $^

%.o : %.c
	cc -c $<

clean:
	rm -rf *.o striptest *~

