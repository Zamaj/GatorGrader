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
	std::string fullName;
	std::vector<Assignment*> assignments;	
public:
	Student();
	Student(std::string first, std::string last, string full);
	std::string getFirstName();
	std::string getLastName();
	std::string getFullName();
	void addStudentAssignment(Assignment *assignment);
	void gradeStudentAssignment(std::string whichAssignment, Course* course);
	void gradeStudentAssignment(std::string assignment, double points, Course* course);
	double getAverageGrade();
	//void getRank();
};