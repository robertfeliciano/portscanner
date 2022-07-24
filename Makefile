CXX=g++
CPPFLAGS=-pthread -Wall

all:
	$(CXX) pscan.cpp -o ps $(CPPFLAGS)

clean:
	rm pscan