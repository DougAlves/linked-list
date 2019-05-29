#include "../include/linkedlist.h"
#include <iostream>
int main (){

    ls::list<int> a;
    ls::list<int> c{1,5,6,7};

    a.push_front(2);
    a.push_front(45);
    a.push_back(25);

    ls::list<int> b(a);
    a.pop_front();
    b.pop_back();
    b = c;
    a.clear();
    try {
        bool t = c==b;
        std::cout << "c: "<< c.front() << std::endl;
        std::cout << "b: "<< b << std::endl;
        std::cout << (c==b) << std::endl;
        std::cout << (c != b) << std::endl;
        std::cout << "a: "<< a.back() << std::endl;
    }catch(const char* e){
        std::cout<< e << std::endl;
    }
}