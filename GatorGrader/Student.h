#pragma once
#include "Assignment.h"
#include "Course.h"
#include "Instructor.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Student {
private:
	std::string firstName;
	std::string lastName;
public:
	Student();
	Student(std::string first, std::string last);
	std::string getFirstName();
	std::string getLastName();
};

Student::Student() {

}

Student::Student(string first, string last) {
	firstName = first;
	lastName = last;
}

string Student::getFirstName() {
	return firstName;
}

string Student::getLastName() {
	return lastName;
}