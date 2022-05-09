#include "stack.hpp"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// UESD THIS GITHUB ACCOUNT : https://github.com/andrestc/linux-prog/blob/master/ch7/malloc.c and 
// https://stackoverflow.com/a/12773678
// FOR MALLOC AND FREE IMPLEMENTATIONS, CALLOC IS DONE BY US


typedef struct alloc {

	struct alloc *next;
	size_t size;

} alloc;

static pthread_mutex_t mutex;
static alloc root_of_allocation_table = {0, 0};
static const size_t align_to = 16;

void* _malloc(size_t size) {

    printf("DEBUG: Using Malloc! \n");

    size = (size + sizeof(alloc) + (align_to - 1)) & ~ (align_to - 1);		// define the size needed for the object
    alloc* block = root_of_allocation_table.next;	
    alloc** head = &(root_of_allocation_table.next);
	// look for free space
    while (block != 0) {
		// if found an empty space big enaugth for our object
        if (block->size >= size) {
            *head = block->next;
            return ((char*)block) + sizeof(alloc);		// pointer to the located address
        }
        head = &(block->next);
        block = block->next;
    }
	// in case there is no free space, create one
    block = (alloc*)sbrk(size);
    block->size = size;
    return ((char*)block) + sizeof(alloc);
}



void *_calloc(size_t size)
{	
    printf("DEBUG: Using Calloc! \n");
	// use malloc and reset the located memory
	void *ptr = _malloc(size);
	memset(ptr, 0, size);
	return ptr;
}


void _free(void *address)
{
    printf("DEBUG: Using Free! \n");
	if (address == NULL)
		return;
    
	pthread_mutex_lock(&mutex);

	alloc* block = (alloc*)(((char*)address) - sizeof(alloc));
	block->next = root_of_allocation_table.next;
	root_of_allocation_table.next = block;

    pthread_mutex_unlock(&mutex);
}

void init()
{
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("\n *alloc mutex init has failed*\n");
	}	
}

/*
~~~~~~~~~~~ STACK FUNCTIONS ~~~~~~~~~~~~~
*/
void push(pnode *head, char data[1024]){
    
    // in case the stack is empty -> the new node will be the head of the stack
    if (*head == NULL)
    {
        *head = (pnode) _malloc(sizeof(node));
        (*head)->data = (char*) _malloc(sizeof(char)*1024);
        memcpy((*head)->data,data, strlen(data));
        (*head)->next = NULL;
    }
    else
    {
        pnode new_node = (pnode) _malloc(sizeof(node));      // dynamic allocation
        new_node->data = (char*) _malloc(sizeof(char)*1024);
        memcpy(new_node->data,data, strlen(data));
        new_node->next = NULL;
        pnode *ptr = head;  //temporary pointer
        while ((*ptr)->next)
        {
            // loop until the last node in the stack
            ptr = &((*ptr)->next);      // increament the pointer
        }
        (*ptr)->next = new_node;     // add the new node to the stack
    }
}

void pop(pnode *head){

    // remove the last node from the stack

    if (*head == NULL){
        // stack is empty, return while doing nothing
        return;
    }
    pnode *ptr = head;  //temporary pointer
    while ((*ptr)->next)
    {
        // loop until the one befre the last node in the stack
        ptr = &((*ptr)->next);      // increament the pointer
    }
    pnode del = (*ptr);    // the node we want to delete
    (*ptr) = NULL;    // remove the last node from the stack

    // free the deleted node
    _free(del); 
}

char* top(pnode *head){

    // return the data of the last node in the stack

    // if the stack is empty -> return empty string
    if (*head == NULL){
        return NULL;
    }

    // loop until the last node
    pnode *ptr = head;  //temporary pointer
    while ((*ptr)->next)
    {
        // loop until the last node in the stack
        ptr = &((*ptr)->next);      // increament the pointer
    }
    return (*ptr)->data;
}

