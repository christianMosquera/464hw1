CXX=gcc
CXXFLAGS=-std=c++17 -g -pedantic -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer

all: server pincracktest

server: server.c
	gcc -o server server.c -lcrypto -lssl

pincracktest: pincrack.c
	gcc -c -o libpincrack.a pincrack.c
	gcc -o pincracktest -L. pincracktest.c -lpincrack

clean:
	rm -f server pincrack *.o *.a *.out




