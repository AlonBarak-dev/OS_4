#include "stack.hpp"
#include <vector>
#include <string>
#include <iostream>


using namespace std;

bool Stack::push(string str){
    this->stck.push_back(str);
    this->lastindex++;
    this->size++;
    return true;
}

void Stack::pop(){
    try{
        this->stck.pop_back();
        this->lastindex--;
    }
    catch(exception &e){
        throw runtime_error("Empty stack!");
    }
}

string Stack::top(){
    try{
        string str = this->stck.at(this->lastindex);
        return str;
    }
    catch(exception& e){
        throw runtime_error("Empty stack!");
    }
}
