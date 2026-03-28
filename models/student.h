#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

// ============================================================
//  DERIVED CLASS: Student (inherits from Person)
//  A Student IS-A Person with an added student number
//  and grade. Overrides getProfile() to show student info.
// ============================================================
class Student : public Person
{
protected:
    int studentNumber;
    int grade; // 0 - 100

public:
    // Constructor — passes name and age up to Person via initialiser list
    Student(string name, int age, int studentNumber, int grade)
        : Person(name, age), studentNumber(studentNumber), grade(grade) {}

    virtual ~Student() {}

    // Getters
    int getStudentNumber() const { return studentNumber; }
    int getGrade() const { return grade; }
    void setGrade(int g) { grade = g; }

    // Override getProfile() from Person
    void getProfile() const override
    {
        cout << "  [Student]   " << name
             << " | No: " << studentNumber
             << " | Age: " << age
             << " | Grade: " << grade << "%"
             << endl;
    }
};

#endif