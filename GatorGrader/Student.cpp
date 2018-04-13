#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include "Student.h"

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