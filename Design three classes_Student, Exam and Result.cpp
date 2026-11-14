//8. Design three classes: Student, Exam and Result. The student class has data members such as roll no, name etc. Create a class Exam by inheriting the
//Student class. The Exam class adds data members representing the marks scored in six subjects. Derive the Result from class Exam and it has its own
//members such as total marks. Write an interactive program to model this relationship. What type of inheritance this model belongs to

#include <iostream>
#include <string>

class Student {
protected:
    int rollNo;
    std::string name;

public:
    void getStudentData() {
        std::cout << "Enter Roll Number: ";
        std::cin >> rollNo;
        std::cout << "Enter Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
    }

    void putStudentData() const {
        std::cout << "Roll Number: " << rollNo << std::endl;
        std::cout << "Name: " << name << std::endl;
    }
};

class Exam : public Student {
protected:
    float marks[6];

public:
    void getExamData() {
        getStudentData();
        std::cout << "Enter marks for 6 subjects:" << std::endl;
        for (int i = 0; i < 6; ++i) {
            std::cout << "Subject " << i + 1 << ": ";
            std::cin >> marks[i];
        }
    }

    void putExamData() const {
        putStudentData();
        std::cout << "Marks: ";
        for (int i = 0; i < 6; ++i) {
            std::cout << marks[i] << " ";
        }
        std::cout << std::endl;
    }
};

class Result : public Exam {
private:
    float totalMarks;
    float percentage;

public:
    void calculateResult() {
        getExamData();
        totalMarks = 0;
        for (int i = 0; i < 6; ++i) {
            totalMarks += marks[i];
        }
        percentage = totalMarks / 6.0f;
    }

    void displayResult() const {
        std::cout << "\n--- Student Result ---" << std::endl;
        putExamData();
        std::cout << "Total Marks: " << totalMarks << " / 600" << std::endl;
        std::cout << "Percentage: " << percentage << "%" << std::endl;
    }
};

int main() {
    Result studentResult;
    studentResult.calculateResult();
    studentResult.displayResult();
    return 0;
}