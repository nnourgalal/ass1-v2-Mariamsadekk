#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
#using namespace std;

class Student {
private:
    int yearLevel;
    string major;
public:
    Student(int yl, string m) {
        yearLevel = yl;
        major = m;
        void display();
    }
};













#endif
