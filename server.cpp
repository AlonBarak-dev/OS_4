/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "stack.hpp"
#include <iostream>       // std::cout
#include <mutex>          // std::mutex

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

struct arg_struct {
    int arg1;
    pnode *head;
};


void push(pnode *head, char data[1024]); // push -> receives head of stack (double pointer) & data array
void pop(pnode *head);  // pop -> receives head of stack (double pointer)
char* top(pnode head);  // top -> receives head of stack (pointer)
std::mutex lock;        // mutex lock 

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void *send_to_user(void *args)
{
    
    struct arg_struct *argss = (struct arg_struct *)args;
    int new_fd = argss->arg1;
    
    sleep(5);
    char buffer[1024] = {0};
    while(true){
        read(new_fd, buffer, 1024);
        if (strncmp(buffer, "PUSH ",5) == 0)
        {
            // the PUSH command is executed
            std::cout << "waiting" << std::endl;
            lock.lock();
            std::cout << "DEBUG:push" << std::endl;       // DEBUG 
            push(argss->head, buffer+5);  // push the input of the buffer into the stack
            lock.unlock();
        }
        else if (strncmp(buffer, "TOP",3) == 0)
        {
            // the POP command is executed
            lock.lock();
            std::cout << "DEBUG:top" << std::endl;       // DEBUG 
            char* str = top(argss->head);      // top the last node of the stack
            sleep(3);
            if(send(new_fd, str, strlen(str),0) == -1){
                perror("send error!");
            }
            std::cout << "DEBUG:msg sent" << std::endl;       // DEBUG 
            lock.unlock();
        }
        else if (strncmp(buffer, "POP",3) == 0)
        {
            // the POP command is executed
            lock.lock();
            std::cout << "DEBUG:pop" << std::endl;       // DEBUG 
            pop(argss->head);     // pop the last node from the stack
            lock.unlock();
        }
        else if (strcmp(buffer, "EXIT") == 0){
            std::cout << "DEBUG:exit" << std::endl;       // DEBUG 
            break;
        }
        bzero(buffer, 1024);
    }
    
    close(new_fd);
    free(args);
    return NULL;
}

int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    
    pnode head = NULL;      // head of the stack


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        pthread_t thread_id;
        // int *args = (int*) malloc(sizeof(int));
        // *args = new_fd;
        struct arg_struct args;
        args.arg1 = new_fd;
        args.head = &head;
        pthread_create(&thread_id, NULL, send_to_user, (void*)&args);
        
    }

    return 0;
}