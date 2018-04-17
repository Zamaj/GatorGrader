#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Assignment;
class Course;

class Student {
private:
	std::string firstName;
	std::string lastName;
	std::vector<Assignment*> assignments;
public:
	Student();
	Student(std::string first, std::string last);
	std::string getFirstName();
	std::string getLastName();
	void addStudentAssignment(Assignment *assignment);
	void gradeStudentAssignment(string assignmentname, double points);
};