//11. Write a program to calculate the total mark of a student using the concept of virtual base class.

#include <iostream>

class Student {
protected:
    int rollNo;

public:
    void getNumber() {
        std::cout << "Enter Roll Number: ";
        std::cin >> rollNo;
    }

    void putNumber() const {
        std::cout << "Roll Number: " << rollNo << std::endl;
    }
};

class Test : virtual public Student {
protected:
    float sub1, sub2;

public:
    void getMarks() {
        std::cout << "Enter marks for two subjects: ";
        std::cin >> sub1 >> sub2;
    }

    void putMarks() const {
        std::cout << "Marks obtained: " << sub1 << ", " << sub2 << std::endl;
    }
};

class Sports : virtual public Student {
protected:
    float score;

public:
    void getScore() {
        std::cout << "Enter sports score: ";
        std::cin >> score;
    }

    void putScore() const {
        std::cout << "Sports Score: " << score << std::endl;
    }
};

class Result : public Test, public Sports {
private:
    float total;

public:
    void display() {
        getNumber();
        getMarks();
        getScore();

        total = sub1 + sub2 + score;

        std::cout << "\n--- Result Summary ---" << std::endl;
        putNumber();
        putMarks();
        putScore();
        std::cout << "Total Score: " << total << std::endl;
    }
};

int main() {
    Result studentResult;
    studentResult.display();
    return 0;
}