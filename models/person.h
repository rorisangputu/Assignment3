#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

// ============================================================
//  BASE CLASS: Person
//  Every person in the university system has a name and age.
//  getProfile() is declared virtual so that subclasses can
//  override it — this is what enables polymorphism.
// ============================================================
class Person
{
protected:
    string name;
    int age;

public:
    // Constructor
    Person(string name, int age) : name(name), age(age) {}

    // Virtual destructor — required when using inheritance
    virtual ~Person() {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }

    // Pure virtual function — forces every subclass to implement it
    // This makes Person an ABSTRACT class (cannot be instantiated directly)
    virtual void getProfile() const = 0;
};

#endif