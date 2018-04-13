#pragma once
//#include "Assignment.h"
//#include "Student.h"
//#include "Instructor.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Assignment;
class Student;

class Course {
private:
	std::string courseName;
	std::vector<Student*> studentList;
	std::vector<Assignment*> assignmentList;
public:
	Course(std::string name);
	void setCourseName(std::string name);
	std::string getCourseName();
	void showCourseOptions();
	void addStudent();
	void addStudent(std::string first, std::string last);
	void addAssignment();
	void addAssignment(std::string name, double points);
	void print();
	void courseMenu();
	void refresh();
};