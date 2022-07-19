GCC=gcc
CFLAGS=-lpthread -Wall

all:
	$(GCC) $(CFLAGS) pscan.c -o pscan

clean:
	rm pscan