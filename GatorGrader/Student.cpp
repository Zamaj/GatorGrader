// #include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Student.h"
#include "Assignment.h"
#include "Course.h"
#include "Instructor.h"

Student::Student() {

}

Student::Student(string first, string last) {
	firstName = first;
	lastName = last;
}

std::string Student::getFirstName() {
	return firstName;
}

std::string Student::getLastName() {
	return lastName;
}

void Student::addStudentAssignment(Assignment *assignment) {
	assignments.push_back(assignment);
}