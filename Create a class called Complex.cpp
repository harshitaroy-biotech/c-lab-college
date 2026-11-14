//6. Create a class called Complex for performing following operations:
//(a) Overload increment and decrement operators for increasing and decreasing complex number values (Unary operator overload).
//(b) Overload ‘+’ op and ‘-‘op for complex numbers (Binary operator overloading).

#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator++() {
        ++real;
        ++imag;
        return *this;
    }

    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        ++imag;
        return temp;
    }

    Complex operator--() {
        --real;
        --imag;
        return *this;
    }

    Complex operator--(int) {
        Complex temp = *this;
        --real;
        --imag;
        return temp;
    }

    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, imag - c.imag);
    }

    void display() const {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main() {
    Complex c1(3.5, 2.5);
    Complex c2(1.5, 1.0);

    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    
    ++c1;
    --c2;

    std::cout << "c1 after increment: ";
    c1.display();

    std::cout << "c2 after decrement: ";
    c2.display();

    std::cout << "Sum (c1 + c2): ";
    c3.display();

    std::cout << "Difference (c1 - c2): ";
    c4.display();

    return 0;
}