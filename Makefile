CXX=g++
CPPFLAGS=-pthread -Wall -std=c++11

all:
	$(CXX) pscan.cpp -o ps $(CPPFLAGS)

clean:
	rm pscan