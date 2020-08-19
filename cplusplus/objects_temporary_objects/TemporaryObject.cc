#include <iostream>
#include <ostream>

class OtherObject {
    int a;
    public:
    OtherObject();
    ~OtherObject();
    /* OtherObject(int value); */
    OtherObject(const int& reference);
    OtherObject(int* pointer);
    OtherObject(int&& temporary);
};

OtherObject::OtherObject() {
    std::cout << "constructing OtherObject by default - " << this << std::endl;
    this->a = 0;
}

/* OtherObject::OtherObject(int value) { */
/*     std::cout << "constructing OtherObject by value - " << this << std::endl; */
/*     this->a = value; */
/* } */

OtherObject::OtherObject(const int& reference) {
    std::cout << "constructing OtherObject by reference - " << this << std::endl;
    this->a = reference;
}

OtherObject::OtherObject(int* pointer) {
    std::cout << "constructing OtherObject by pointer - " << this << std::endl;
    this->a = *pointer;
}

OtherObject::OtherObject(int&& temporary) {
    std::cout << "constructing OtherObject by temporary - " << this << std::endl;
    this->a = temporary;
}

OtherObject::~OtherObject() {
    std::cout << "\tbye bye OtherObject: " << this << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "hello world!" << std::endl;

    int a = 10;
    int* b;
    b = (int*) malloc(sizeof(int));

    OtherObject defaultConstructor; // default
    OtherObject valueObject(a); // value / const reference
    OtherObject pointerObject(b); // pointer
    OtherObject temporaryObject(10+10); // value / temporary object

    std::cout << "bye bye world!" << std::endl;
}
