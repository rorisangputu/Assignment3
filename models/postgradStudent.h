#ifndef POSTGRAD_STUDENT_H
#define POSTGRAD_STUDENT_H

#include "student.h"

// ============================================================
//  DERIVED CLASS: PostgradStudent (inherits from Student)
//  A PostgradStudent IS-A Student with an additional
//  research topic. Overrides getProfile() again to show
//  the extra information.
//
//  This completes the 3-level inheritance chain:
//  Person -> Student -> PostgradStudent
// ============================================================
class PostgradStudent : public Student
{
private:
    string researchTopic;

public:
    PostgradStudent(string name, int age, int studentNumber,
                    int grade, string researchTopic)
        : Student(name, age, studentNumber, grade),
          researchTopic(researchTopic) {}

    ~PostgradStudent() {}

    string getResearchTopic() const { return researchTopic; }

    // Override getProfile() — polymorphism in action:
    // calling getProfile() on a Person* that holds a
    // PostgradStudent will run THIS version
    void getProfile() const override
    {
        cout << "  [Postgrad]  " << name
             << " | No: " << studentNumber
             << " | Age: " << age
             << " | Grade: " << grade << "%"
             << " | Research: " << researchTopic
             << endl;
    }
};

#endif