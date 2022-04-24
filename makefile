OBJS	= server.o stack.o
SOURCE	= server.cpp stack.cpp
HEADER	= stack.hpp
OUT	= server
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: server client test

server: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

client: client.o
	$(CC) client.o -o client 

test: test.o stack.o
	$(CC) test.o stack.o -o test

server.o: server.cpp 
	$(CC) $(FLAGS) server.cpp

stack.o: stack.cpp
	$(CC) $(FLAGS) stack.cpp

client.o: client.cpp
	$(CC) -c client.cpp

test.o: test.cpp
	$(CC) -c test.cpp

clean:
	rm -f $(OBJS) $(OUT) client *.o