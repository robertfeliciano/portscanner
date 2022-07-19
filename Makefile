GCC=g++
CFLAGS=-pthread -Wall

all:
	$(GCC) pscan.cpp $(CFLAGS)