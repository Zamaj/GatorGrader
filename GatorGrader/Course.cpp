#include "stdafx.h"
#include "Assignment.h"
#include "Student.h"
#include "Course.h"
#include "Instructor.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

Course::Course(string name) {
	courseName = name;
}

Course::~Course() {
	string line;

	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	
	while (getline(file, line)) {

		if (!(line.substr(1, line.back()) == courseName || line.substr(0, courseName.size()) == courseName)) {
			temp << line << endl;
		}		
	}	

	file.close();
	temp.close();

	remove("courses.txt");
	rename("temp.txt", "courses.txt");
}

void Course::setCourseName(string name) {
	courseName = name;
}

string Course::getCourseName() {
	return courseName;
}

string Course::tag(bool whichType) {

	string tag;

	if (whichType == 0) {
		tag = getCourseName().append("$");
		return 	tag;
	}

	if (whichType == 1) {
		tag = getCourseName().append("@");
		return tag;
	}	
}

void Course::addStudent() {
	string newStudentName;
	string newStudentFirstName;
	string newStudentLastName;

	cout << "Please enter sutdent's first and last name:" << endl;
	getline(cin, newStudentName);

	istringstream studentAttributes(newStudentName);
	studentAttributes >> newStudentFirstName >> newStudentLastName;

	Student *student = new Student(newStudentFirstName, newStudentLastName);
	studentList.push_back(student);

	save(newStudentName, 0);

	cout << "Student '" << newStudentFirstName << newStudentLastName << "' added to course " << courseName << endl;
}

void Course::addStudent(string first, string last) {
	Student *student = new Student(first, last);
	studentList.push_back(student);
}

void Course::addAssignment() {	

	string newAssignmentName;
	string newAssignmentPoints;
	double points;

	cout << "Assignment Name:" << endl;
	getline(cin, newAssignmentName);
	
	cout << "Assignment points:" << endl;
	getline(cin, newAssignmentPoints);

	points = atof(newAssignmentPoints.c_str());

	Assignment *assignment = new Assignment(newAssignmentName, points);
	assignmentList.push_back(assignment);

	save(newAssignmentName, 1);

	cout << "Assignment '" << newAssignmentName << "' worth " << points << " points has been added to course " << courseName << endl;
}

void Course::addAssignment(string name, double points) {
	Assignment *assignment = new Assignment(name, points);
	assignmentList.push_back(assignment);
}

void Course::save(string newItem, bool whichType) {

	string line;
	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	vector<string> fileContent;
	vector<string>::iterator it;

	while (getline(file, line)) {
		fileContent.push_back(line);
	}

	for (it = fileContent.begin(); it != fileContent.end(); it++) {
		if (it->substr(1, it->back()) == courseName) {
			fileContent.insert(it + 1, newItem.insert(0, tag(whichType)));
			break;
		}
	}

	vector<string>::iterator write;

	for (write = fileContent.begin(); write != fileContent.end(); write++) {
		temp << *write << endl;
	}

	file.close();
	temp.close();

	remove("courses.txt");
	rename("temp.txt", "courses.txt");	
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
	string menuChoice;

	cout << "What would you like to do in " << courseName << "?" << endl;
	cout << "1. New assignment" << endl;
	cout << "2. Add student(s)" << endl;

	getline(cin, menuChoice);

	if (menuChoice == "1" || menuChoice == "New assignment" || menuChoice == "new assignment" || menuChoice == "New Assignment") {
		addAssignment();
	}

	if (menuChoice == "2") {
		addStudent();
	}
}