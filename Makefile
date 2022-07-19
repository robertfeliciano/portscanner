GCC=g++
CFLAGS=-lpthread -Wall

all: pscan
	$(GCC) $(CFLAGS) pscan.c -o pscan

clean:
	rm pscan