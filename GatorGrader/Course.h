#include "Assignment.h"
#include "Student.h"
#include "Instructor.h"
#include <string>
#include <vector>
#include <fstream>

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
};

Course::Course(string name) {
	courseName = name;
}

void Course::setCourseName(string name) {
	courseName = name;
}

string Course::getCourseName() {
	return courseName;
}

void Course::showCourseOptions() {

}

void Course::addStudent() {

}

void Course::addStudent(string first, string last) {
	Student *student = new Student(first, last);
	studentList.push_back(student);
}

void Course::addAssignment() {

}

void Course::addAssignment(string name, double points) {
	Assignment *assignment = new Assignment(name, points);
	assignmentList.push_back(assignment);
}

void Course::print() {

	cout << courseName << endl;

	cout << "Students:" << endl;
	for (unsigned int i = 0; i < studentList.size(); i++) {
		cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << ", ";
	}

	cout << endl;

	cout << "Assignments:" << endl;
	for (unsigned int i = 0; i < assignmentList.size(); i++) {
		cout << assignmentList[i]->getAssignmentName() << ", ";
	}
}

void Course::courseMenu() {
	cout << "What would you like to do in " << courseName << "?" << endl;
	cout << "1. New assignment" << endl;
	cout << "2. Add student(s)" << endl;
}
