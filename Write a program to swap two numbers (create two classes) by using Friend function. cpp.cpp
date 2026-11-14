//9. Write a program to swap two numbers (create two classes) by using Friend function. 


#include <iostream>

class ClassB;

class ClassA {
private:
    int numA;

public:
    ClassA(int a) : numA(a) {}

    void display() const {
        std::cout << "Value in ClassA: " << numA << std::endl;
    }

    friend void swapValues(ClassA&, ClassB&);
};

class ClassB {
private:
    int numB;

public:
    ClassB(int b) : numB(b) {}

    void display() const {
        std::cout << "Value in ClassB: " << numB << std::endl;
    }

    friend void swapValues(ClassA&, ClassB&);
};

void swapValues(ClassA& objA, ClassB& objB) {
    int temp = objA.numA;
    objA.numA = objB.numB;
    objB.numB = temp;
}

int main() {
    ClassA objA(10);
    ClassB objB(20);

    std::cout << "Before swapping:" << std::endl;
    objA.display();
    objB.display();

    swapValues(objA, objB);

    std::cout << "\nAfter swapping:" << std::endl;
    objA.display();
    objB.display();

    return 0;
}