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

    printf("Run succesfully\n");

    // free the stack
    free(st);

    // ~~~~~~~~~~~~~~~~~~~~~~~~ DONE WITH STACK'S TESTS ~~~~~~~~~~~~~~~~~~~~~~~~~~


    // ~~~~~~~~~~~~~~~~~~~~~~~~ TESTS FOR THE WHOLE CLIENT-SERVER SYSTEM ~~~~~~~~~

    /*
        Please make sure that the server is running before those tests!
    */

    pid_t pid_first = fork(); // create a new process
    if (pid_first < 0)
    {
        // fail
        printf("Failed to create a new CLient");
    }

    if (pid_first == 0)
    {
        // child process
        char cmd[] = "./client_test1";
        char *child_args;
        char * argv[] = {cmd, NULL};
        // run the client
        execvp(argv[0], argv);
        exit(127);
    }
    else{
        // parent process
        sleep(2);
        pid_t pid_second = fork(); // create a new process
        if (pid_second < 0)
        {
            // fail
            printf("Failed to create a new CLient");
        }

        if (pid_second == 0)
        {
            // child process
            char cmd[] = "./client_test2";
            char * argv[] = {cmd, NULL};
            // run the client
            execvp(argv[0], argv);
            exit(127);
        }
        else{
            // parent process
            sleep(2);
            pid_t pid_third = fork(); // create a new process
            if (pid_third < 0)
            {
                // fail
                printf("Failed to create a new CLient");
            }

            if (pid_third == 0)
            {
                // child process
                char cmd[] = "./client_test3";
                char * argv[] = {cmd, NULL};
                // run the client
                execvp(argv[0], argv);
                exit(127);
            }
            else{
                int status;
                while (waitpid(pid_third, &status,0) == -1)
                {
                    if (errno != EINTR)
                    {
                        status = -1;
                        break;
                    }
                }   
            }   // third process

            int status;
            while (waitpid(pid_second, &status,0) == -1)
            {
                if (errno != EINTR)
                {
                    status = -1;
                    break;
                }
            }   
        }   // second process


        int status;
        while (waitpid(pid_first, &status,0) == -1)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }   

    }   // first process
    
    




    return 0;
}