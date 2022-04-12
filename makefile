OBJS	= server.o
SOURCE	= server.cpp
HEADER	= 
OUT	= server.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

server.o: server.cpp
	$(CC) $(FLAGS) server.cpp


clean:
	rm -f $(OBJS) $(OUT)