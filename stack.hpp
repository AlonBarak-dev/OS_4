#include <vector> 
#include <iostream>
#include <string>




class Stack
{
private:
    
    int size;
    int lastindex;
    std::vector<std::string> stck;

public:
    Stack() : size(0), lastindex(-1){}
    ~Stack(){}
    bool push(std::string str);
    void pop();
    std::string top();
};
