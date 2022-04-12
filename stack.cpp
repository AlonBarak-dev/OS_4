#include "stack.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(pnode *head, char data[1024]){
    
    // in case the stack is empty -> the new node will be the head of the stack
    if (*head == NULL)
    {
        *head = (pnode) malloc(sizeof(node));
        (*head)->data = (char*) malloc(sizeof(char)*1024);
        memcpy((*head)->data,data, strlen(data));
        (*head)->next = NULL;
    }
    else
    {
        pnode new_node = (pnode) malloc(sizeof(node));      // dynamic allocation
        new_node->data = (char*) malloc(sizeof(char)*1024);
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
    while ((*ptr)->next->next)
    {
        // loop until the one befre the last node in the stack
        ptr = &((*ptr)->next);      // increament the pointer
    }
    pnode del = (*ptr)->next;    // the node we want to delete
    (*ptr)->next = NULL;    // remove the last node from the stack

    // free the deleted node
    free(del); 
}

char* top(pnode *head){

    // return the data of the last node in the stack
    // loop until the last node
    pnode *ptr = head;  //temporary pointer
    while ((*ptr)->next)
    {
        // loop until the last node in the stack
        ptr = &((*ptr)->next);      // increament the pointer
    }
    return (*ptr)->data;
}


// using namespace std;

// bool Stack::push(string str){
//     this->stck.push_back(str);
//     this->lastindex++;
//     this->size++;
//     return true;
// }

// void Stack::pop(){
//     try{
//         this->stck.pop_back();
//         this->lastindex--;
//     }
//     catch(exception &e){
//         throw runtime_error("Empty stack!");
//     }
// }

// string Stack::top(){
//     try{
//         string str = this->stck.at(this->lastindex);
//         return str;
//     }
//     catch(exception& e){
//         throw runtime_error("Empty stack!");
//     }
// }
