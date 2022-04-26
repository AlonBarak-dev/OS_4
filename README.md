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
3. Run a Client - $ ./client "IP_ADDRESS"

Please noitce that the server is listen on port 3490 at 127.0.0.1

### Test
The test checks if the stack preforms well and also checks the whole system 
with three different clients (Processes).
the clients receives their input from the text file "test.txt".
in order to run the test do the following:
1. Compile the code - $ make 
2. Run the Test - $ ./test

Ignore the prints on the screen, its the process log.

P.S. The client connect directly to the server and no work should be done by the user!
