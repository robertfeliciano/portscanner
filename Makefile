GCC=gcc
CFLAGS=-lpthread -Wall

all:
	$(GCC) pscan.c -o pscan $(CFLAGS)

clean:
	rm pscan