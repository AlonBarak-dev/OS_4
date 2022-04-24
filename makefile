OBJS	= server.o stack.o
SOURCE	= server.cpp stack.cpp
HEADER	= stack.hpp
OUT	= server
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: server client test client_test1 client_test2 client_test3

server: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

client: client.o
	$(CC) client.o -o client 

client_test1: client_test1.o
	$(CC) -g client_test1.o -o client_test1 

client_test2: client_test2.o
	$(CC) -g client_test2.o -o client_test2 

client_test3: client_test3.o
	$(CC) -g client_test3.o -o client_test3 

test: test.o stack.o
	$(CC) test.o stack.o -o test

server.o: server.cpp 
	$(CC) $(FLAGS) server.cpp

stack.o: stack.cpp
	$(CC) $(FLAGS) stack.cpp

client.o: client.cpp
	$(CC) -c client.cpp

client_test1.o: client_test1.cpp
	$(CC) -c client_test1.cpp

client_test2.o: client_test2.cpp
	$(CC) -c client_test2.cpp

client_test3.o: client_test3.cpp
	$(CC) -c client_test3.cpp

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -f $(OBJS) $(OUT) client *.o test client_test1 client_test2 client_test3