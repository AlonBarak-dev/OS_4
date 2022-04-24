#include "stack.hpp"
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>

void push(pnode *head, char data[1024]); // push -> receives head of stack (double pointer) & data array
void pop(pnode *head);  // pop -> receives head of stack (double pointer)
char* top(pnode head);  // top -> receives head of stack (pointer)


int main(){

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


    return 0;
}