//7. Write a program to find the area (function name AREA) of circle, rectangle and triangle by Function overloading concept. 

#include <iostream>
#include <cmath>

double AREA(double radius) {
    return 3.141592653589793 * radius * radius;
}

double AREA(double length, double breadth) {
    return length * breadth;
}

double AREA(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    double radius = 5.0;
    std::cout << "Area of circle: " << AREA(radius) << std::endl;

    double length = 4.0;
    double breadth = 6.0;
    std::cout << "Area of rectangle: " << AREA(length, breadth) << std::endl;

    double side1 = 3.0;
    double side2 = 4.0;
    double side3 = 5.0;
    std::cout << "Area of triangle: " << AREA(side1, side2, side3) << std::endl;

    return 0;
}