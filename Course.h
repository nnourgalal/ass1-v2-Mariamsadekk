#ifndef COURSE_H
#define COURSE_H

#include <string>
#include "Student.h"
using namespace std;
class Course{
private:
    string courseCode;
    string courseName;
int maxStudents;
int currentStudents;

public:
addStudent(const Student& s);
void displayCourseInfo();
};













#endif
