#include "stack.hpp"
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void push(pnode *head, char data[1024]); // push -> receives head of stack (double pointer) & data array
void pop(pnode *head);  // pop -> receives head of stack (double pointer)
char* top(pnode head);  // top -> receives head of stack (pointer)
void* _malloc(size_t size);
void _free(void *ptr);
void _calloc(void *address);

int main(){

    // ~~~~~~~~~~~~~~~~~~~~~ TESTS FOR THE STACK STRUCT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pnode st = (pnode)malloc(sizeof(node));     // inititalize a stack
    char buffer[1024] = {0};
    // push "hello" into ths stack
    memcpy(buffer, "hello", 5);
    push(&st, buffer);

    // top the head of the stack and assert its equal to "hello"
    assert(memcmp(top(&st), buffer, 5) == 0);

    // clean the buffer
    memset(buffer, 0 , 1024);
    
    // push "world" into the stack
    memcpy(buffer, "world", 5);
    push(&st,buffer);

    // top the head of the stack and assert it is equal to "world"
    assert(memcmp(top(&st), buffer, 5) == 0);

    // clean the buffer
    memset(buffer, 0 , 1024);

    // pop the head of the stack
    pop(&st);

    // assert the head of the stack is "hello" once again
    memcpy(buffer, "hello", 5);
    assert(memcmp(top(&st), buffer, 5) == 0);

    printf("Stack Test run succesfully\n");

    // free the stack
    free(st);

    // ~~~~~~~~~~~~~~~~~~~~~~~~ DONE WITH STACK'S TESTS ~~~~~~~~~~~~~~~~~~~~~~~~~~


    // ~~~~~~~~~~~~~~~~~~~~~~~~ TESTS FOR THE WHOLE CLIENT-SERVER SYSTEM ~~~~~~~~~

    /*
        Please make sure that the server is running before those tests!
    */

    pid_t pid;
    pid = fork();
    // in case of an error while creating a new process
    if (pid < 0)
    {
        printf("failed to create a new Child");
        exit(-1);
    }
    else if (pid != 0)
    {
        // let the parent procees to run the server
        system("./server");
    }
    else{
        // child process creats new clients
        sleep(2);
        for (size_t i = 0; i < 3; i++)
        {
            pid_t pid_c;
            pid_c = fork(); // new process

            if (pid_c < 0)
            {
                printf("failed to create a new client");
                exit(-1);
            }
            else if(pid_c == 0){
                system("./client 127.0.0.1 < test.txt");   // creates new client in child process
            }
            
        }
        exit(0);
        
    }
    
    
    
    




    return 0;
}