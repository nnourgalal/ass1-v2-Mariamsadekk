
#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Instructor.h"
#include "Course.h"
#include "Portal.h"

using namespace std;
// ---------------- Person.cpp-like definitions ----------------
Person::Person() : name(""), id(0) {}
Person::Person(const string& name, int id) : name(name), id(id) {}
Person::~Person() {}

void Person::setName(const string& name) { this->name = name; }
string Person::getName() const { return name; }

void Person::setId(int id) { this->id = id; }
int Person::getId() const { return id; }
//display person info()
void Person::display() const {
    cout << "Name: " << name << "\n";
    cout << "ID: " << id << "\n";
}



// ---------------- Student.cpp-like definitions ----------------
Student::Student() : Person(), yearLevel(0), major("") {}
Student::Student(const string& name, int id, int yearLevel, const string& major)
    : Person(name, id), yearLevel(yearLevel), major(major) {}
Student::~Student() {}
//USING YEAR LEVEL
void Student::setYearLevel(int y) { yearLevel = y; }
int Student::getYearLevel() const { return yearLevel; }

void Student::setMajor(const string& m) { major = m; }
string Student::getMajor() const { return major; }

void Student::display() const {
    Person::display();
    // display information
    cout << "Year: " << yearLevel << "\n";
    cout << "Major: " << major << "\n";
}
//yarab tezbot
// ---------------- Instructor.cpp-like definitions ----------------
Instructor::Instructor() : Person(), department(""), experienceYears(0) {}
Instructor::Instructor(const string& name, int id, const string& department, int experienceYears)
    : Person(name, id), department(department), experienceYears(experienceYears) {}
Instructor::~Instructor() {}

void Instructor::setDepartment(const string& d) { department = d; }
string Instructor::getDepartment() const { return department; }

void Instructor::setExperienceYears(int e) { experienceYears = e; }
int Instructor::getExperienceYears() const { return experienceYears; }

void Instructor::display() const {
    Person::display();
    cout << "Department: " << department << "\n";
    cout << "Experience: " << experienceYears << " years\n";
}

// ---------------- Course.cpp-like definitions ----------------
Course::Course() : courseCode(""), courseName(""), maxStudents(0), enrolledStudents(nullptr), currentCount(0) {}
Course::Course(const string& code, const string& name, int maxStudents)
    : courseCode(code), courseName(name), maxStudents(maxStudents), currentCount(0) {
    if (maxStudents > 0) {
        enrolledStudents = new Student*[maxStudents];
        for (int i = 0; i < maxStudents; ++i) enrolledStudents[i] = nullptr;
    } else enrolledStudents = nullptr;
}

Course::~Course() {
    // Do NOT delete Student objects here — they are owned by Portal (or caller).
    if (enrolledStudents) delete[] enrolledStudents;
}

void Course::setCourseCode(const string& code) { courseCode = code; }
string Course::getCourseCode() const { return courseCode; }

void Course::setCourseName(const string& name) { courseName = name; }
string Course::getCourseName() const { return courseName; }

void Course::setMaxStudents(int m) {
    if (enrolledStudents) delete[] enrolledStudents;
    maxStudents = m;
    currentCount = 0;
    if (m>0) {
        enrolledStudents = new Student*[m];
        for (int i = 0; i < m; ++i) enrolledStudents[i] = nullptr;
    } else enrolledStudents = nullptr;
}
int Course::getMaxStudents() const { return maxStudents; }
int Course::getCurrentCount() const { return currentCount; }

bool Course::addStudent(Student* s) {
    if (currentCount >= maxStudents || enrolledStudents == nullptr) return false;
    enrolledStudents[currentCount++] = s;
    return true;
}

void Course::displayCourseInfo() const {
    cout << "Course: " << courseCode << " - " << courseName << "\n";
    cout << "Max Students: " << maxStudents << "\n";
    cout << "Currently Enrolled:\n";
    for (int i = 0; i < currentCount; ++i) {
        Student* s = enrolledStudents[i];
        if (s) cout << "- " << s->getName() << " (ID: " << s->getId() << ")\n";
    }
}

// ---------------- ProgressReport.cpp-like definitions ----------------


// ---------------- Portal.cpp-like definitions ----------------
Portal::Portal() : courses(nullptr), coursesCount(0), coursesCapacity(0),
                   students(nullptr), studentsCount(0), studentsCapacity(0),
                   instructors(nullptr), instructorsCount(0), instructorsCapacity(0) {}

Portal::~Portal() {
    // delete students
    if (students) {
        for (int i = 0; i < studentsCount; ++i) delete students[i];
        delete[] students;
    }
    // delete instructors
    if (instructors) {
        for (int i = 0; i < instructorsCount; ++i) delete instructors[i];
        delete[] instructors;
    }
    // delete courses
    if (courses) {
        for (int i = 0; i < coursesCount; ++i) delete courses[i];
        delete[] courses;
    }
}

void Portal::initializePortal() {
    Course::Course("1234", "Math", 250);
    Course::Course("1235", "English", 250);
    Course::Course("1236", "Programming", 250);
    Student::Student("nour", 123, 1234, "Math");
    Student::Student("sarah", 234, 1235, "English");
    Student::Student("ahmed", 312, 1236, "Programming");
    Instructor::Instructor("Dr.Ali",9000,"Math", 1234);
    

    addCourse(new Course("CS101", "Introduction to Programming", 3));
    addCourse(new Course("CS102", "Data Structures", 2));
    addStudent(new Student("Sara Ahmed", 2201, 2, "Informatics"));
    addStudent(new Student("Omar Nabil", 2202, 3, "Computer Science"));
    addStudent(new Student("Mona Ali", 2203, 1, "Informatics"));
    addInstructor(new Instructor("Dr. Lina Khaled", 9001, "Computer Science", 5));
    cout << "Educational Portal initialized successfully.\n\n";
    
    
}

void Portal::addCourse(Course* c) {
    if (coursesCapacity == 0) {
        coursesCapacity = 2;
        courses = new Course*[coursesCapacity];
        for (int i = 0; i < coursesCapacity; ++i) courses[i] = nullptr;
    } else if (coursesCount >= coursesCapacity) {
        int newCap = coursesCapacity * 2;
        Course** tmp = new Course*[newCap];
        for (int i = 0; i < newCap; ++i) tmp[i] = (i < coursesCount ? courses[i] : nullptr);
        delete[] courses;
        courses = tmp;
        coursesCapacity = newCap;
    }
    courses[coursesCount++] = c;
}

void Portal::addStudent(Student* s) {
    if (studentsCapacity == 0) {
        studentsCapacity = 2;
        students = new Student*[studentsCapacity];
        for (int i = 0; i < studentsCapacity; ++i) students[i] = nullptr;
    } else if (studentsCount >= studentsCapacity) {
        int newCap = studentsCapacity * 2;
        Student** tmp = new Student*[newCap];
        for (int i = 0; i < newCap; ++i) tmp[i] = (i < studentsCount ? students[i] : nullptr);
        delete[] students;
        students = tmp;
        studentsCapacity = newCap;
    }
    students[studentsCount++] = s;
}

void Portal::addInstructor(Instructor* i) {
    if (instructorsCapacity == 0) {
        instructorsCapacity = 2;
        instructors = new Instructor*[instructorsCapacity];
        for (int j = 0; j < instructorsCapacity; ++j) instructors[j] = nullptr;
    } else if (instructorsCount >= instructorsCapacity) {
        int newCap = instructorsCapacity * 2;
        Instructor** tmp = new Instructor*[newCap];
        for (int k = 0; k < newCap; ++k) tmp[k] = (k < instructorsCount ? instructors[k] : nullptr);
        delete[] instructors;
        instructors = tmp;
        instructorsCapacity = newCap;
    }
    instructors[instructorsCount++] = i;
}

bool Portal::enrollStudentInCourse(Student* s, Course* c) {
    if (!s || !c) return false;
    return c->addStudent(s);
}

void Portal::displayPortalInfo() const {
    // Display courses with enrolled students
    for (int i = 0; i < coursesCount; ++i) {
        cout << "";
        courses[i]->displayCourseInfo();
        cout << "\n";
    }

    // Instructors
    cout << "Instructor Info:\n";
    for (int i = 0; i < instructorsCount; ++i) {
        instructors[i]->display();
        cout << "\n";
    }

    // Students
    cout << "Student Info:\n";
    for (int i = 0; i < studentsCount; ++i) {
        students[i]->display();
        cout << "\n";
    }
}
//test main function
// ---------------- main ----------------
int main() {
    // Portal portal;
    // portal.initializePortal();
    Portal p2;
    p2.initializePortal();
    Course* demoCourse = new Course("CS101", "Introduction to Programming", 3);
    
    Student* s2 = new Student("Omar Nabil", 2202, 2, "Informatics");
    demoCourse->addStudent(s2);
    p2.addCourse(demoCourse);
    p2.addStudent(s2);

    // Also add an instructor and show info
    Instructor* ins = new Instructor("Dr. Lina Khaled", 9001, "Computer Science", 5);
    p2.addInstructor(ins);
    
    // Display full portal info
    p2.displayPortalInfo();

    return 0;
}
