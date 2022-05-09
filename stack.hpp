#ifndef STACK_
#define STACK_
#include <stdio.h>


typedef struct stack_node
{
    char* data;
    struct stack_node *next;
} node, *pnode;

void push(pnode *head, char data[1024]); // push -> receives head of stack (double pointer) & data array
void pop(pnode *head);  // pop -> receives head of stack (double pointer)
char* top(pnode *head);  // top -> receives head of stack (pointer)

void* _malloc(size_t size);
void* _calloc(size_t size);
void _free(void *address);

#endif

