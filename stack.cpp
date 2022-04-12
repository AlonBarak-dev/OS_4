#include "stack.hpp"
#include <vector>
#include <string>
#include <iostream>


using namespace std;

bool stack::push(string str){
    this->stck.push_back(str);
    this->lastindex++;
    this->size++;
    return true;
}

string stack::pop(){
    try{
        string str = this->stck.at(this->lastindex);
        this->stck.pop_back();
        this->lastindex--;
        return str;
    }
    catch(exception e){
        cout << "Empty stack!" << endl;
    }
}

string stack::top(){
    try{
        string str = this->stck.at(this->lastindex);
        return str;
    }
    catch(exception e){
        cout << "Empty stack!" << endl;
    }
}
