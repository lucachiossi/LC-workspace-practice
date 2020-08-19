/* file containing BIG FIVE definitions */

#include "Data.h"
#include <cstdlib>
#include <iostream>
#include <ostream>

int Resource::getThirdInt() {
    return this->thirdInteger;
}

void Object::printInt() {
    std::cout << "Object printInt:" << this;
    std::cout << "\tfirstInteger: " << this->firstInteger << std::endl;
    std::cout << "\tsecondInteger: " << this->secondInteger << std::endl;
    std::cout << "\tthirdInteger: " << this->rsc->getThirdInt() << std::endl;
}

// Copy Policy
Object& Object::operator=(const Object& obj) {
    std::cout << "copy assignment Object " << this << std::endl;
    Resource* rTemp = new Resource{*(obj.rsc)};
    delete this->rsc;
    this->rsc = rTemp;
    this->firstInteger = obj.firstInteger;
    this->secondInteger = obj.secondInteger;

    return *this;
}

// Move Policy

Object& Object::operator=(Object&& obj) {
    std::cout << "move assignment Object " << this << std::endl;
    delete this->rsc;
    this->firstInteger = obj.firstInteger;
    this->secondInteger = obj.secondInteger;
    this->rsc = obj.rsc;
    obj.rsc = nullptr;
    
    return *this;
}
