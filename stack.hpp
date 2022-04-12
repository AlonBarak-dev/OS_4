#ifndef STACK_
#define STACK_



typedef struct stack_node
{
    char* data;
    struct stack_node *next;
} node, *pnode;

void push(pnode *head, char data[1024]); // push -> receives head of stack (double pointer) & data array
void pop(pnode *head);  // pop -> receives head of stack (double pointer)
char* top(pnode *head);  // top -> receives head of stack (pointer)

#endif

