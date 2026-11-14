//10. Consider an example of book shop which sells books and video tapes. These two classes are inherited from base class called media. The media class has
//command data members such as title and publication. The book class has data members for storing number of pages in a book and tape class has playing
//time in a tape. Each class will have member functions such as read () and show (). In the base class, these members have to be defined as virtual functions.
//Write a program to models the class hierarchy for book shop and processes objects of these classes using pointers to base class. Write the rules of virtual
//functions.

#include <iostream>
#include <string>

class Media {
protected:
    std::string title;
    std::string publication;

public:
    virtual void read() = 0;
    virtual void show() = 0;
    virtual ~Media() {}
};

class Book : public Media {
private:
    int pages;

public:
    void read() override {
        std::cout << "Enter title: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "Enter publication: ";
        std::getline(std::cin, publication);
        std::cout << "Enter number of pages: ";
        std::cin >> pages;
    }

    void show() override {
        std::cout << "\n--- Book Details ---" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Publication: " << publication << std::endl;
        std::cout << "Pages: " << pages << std::endl;
    }
};

class Tape : public Media {
private:
    float playTime;

public:
    void read() override {
        std::cout << "Enter title: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "Enter publication: ";
        std::getline(std::cin, publication);
        std::cout << "Enter playing time (minutes): ";
        std::cin >> playTime;
    }

    void show() override {
        std::cout << "\n--- Tape Details ---" << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Publication: " << publication << std::endl;
        std::cout << "Playing Time: " << playTime << " mins" << std::endl;
    }
};

int main() {
    Media* m1;
    Book b;
    Tape t;

    std::cout << "Enter Book Details:" << std::endl;
    m1 = &b;
    m1->read();

    Media* m2;
    std::cout << "\nEnter Tape Details:" << std::endl;
    m2 = &t;
    m2->read();

    m1->show();
    m2->show();

    return 0;
}