CXX=g++
CPPFLAGS=-pthread -Wall

all:
	$(CXX) pscan.cpp -o pscan $(CPPFLAGS)

clean:
	rm pscan