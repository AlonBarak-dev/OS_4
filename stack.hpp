#include <vector> 
#include <iostream>
#include <string>




class stack
{
private:
    
    int size;
    int lastindex;
    std::vector<std::string> stck;

public:
    stack() : stck(std::vector<std::string>()), size(0), lastindex(-1){}
    ~stack(){}
    bool push(std::string str);
    std::string pop();
    std::string top();
};
