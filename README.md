# OS_4
The fourth assignment of the Operating Systems Course
This repo contains an implementation of a multithreaded server which serves as a stack to its client.
In this project we were inspired by https://github.com/andrestc/linux-prog/blob/master/ch7/malloc.c repo,
for the Malloc and Free functions.
THe server can handle up to 10 clients in real time.
The implementation of the Stack and the Dynamic Memory Allocation functions you can find at the "Stack.cpp" file.
in order to run the project do the following:
1. Compile the code - $ make
2. Run the Server - $ ./server
3. Run a Client - $ ./client

P.S. The client connect directly to the server and no work should be done by the user!
