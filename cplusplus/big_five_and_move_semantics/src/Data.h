/* file containing BIG FIVE declaration */

#ifndef DATA
#define DATA

#include <cstdlib>
#include <ostream>
#include <string>
#include <iostream>

class Resource {
    private:
        int thirdInteger;
    public:
        Resource() :
            thirdInteger(0) {
                std::cout << "default constructor Resource " << this << std::endl;
            }
        explicit Resource(int thirdInteger) :
            thirdInteger(thirdInteger) {
                std::cout << "one argument constructor Resource " << this << std::endl;
            }
        int getThirdInt();
        ~Resource() {
            std::cout << "Resource " << this << std::endl;
        }
};

class Object {
    private:
        int firstInteger;
        int secondInteger;
        Resource* rsc;

    public:
        explicit Object(int firstInteger, int secondInteger, int thirdInteger) :
            firstInteger(firstInteger),
            secondInteger(secondInteger) {
                this->rsc = new Resource(thirdInteger);
                std::cout << "three argument constructor Object " << this << std::endl;
            }
        Object() :
            firstInteger(0),
            secondInteger(0) {
                this->rsc = new Resource();
                std::cout << "default constructor Object " << this << std::endl;
            }
        ~Object() {
            delete this->rsc;
            std::cout << "Object " << this << std::endl;
        }
        void printInt();

        // Copy Policy
        Object& operator=(const Object& obj);

        Object(const Object& obj) :
            firstInteger(obj.firstInteger),
            secondInteger(obj.secondInteger),
            rsc(nullptr) {      // create a new object with same params' values
                if(obj.rsc != nullptr) {
                    rsc = new Resource{*(obj.rsc)};
                }
                std::cout << "copy constructor Object " << this << std::endl;
            }

        // Move Policy
        Object& operator=(Object&& obj);

        Object(Object&& obj) :
            firstInteger(obj.firstInteger),
            secondInteger(obj.secondInteger),
            rsc(obj.rsc) {
                // change owner of the internal object from the temporary obj to the current obj
            obj.rsc = nullptr;
            std::cout << "move constructor Object " << this << std::endl;
        }
};

#endif
