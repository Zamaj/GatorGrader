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

string Course::tag(saveType type) {

	string tag;

	if (type == courseSave) {
		tag = "#";
		return tag;
	}

	if (type == studentSave) {
		tag = getCourseName().append("$");
		return 	tag;
	}

	if (type == assignmentSave) {
		tag = getCourseName().append("@");
		return tag;
	}

	if (type = masterAssignmentSave) {
		tag = getCourseName().append("&");
	}
}

void Course::addStudent() {
	string newStudentName;
	string newStudentFirstName;
	string newStudentLastName;

	cout << "Please enter student's first and last name:" << endl;
	getline(cin, newStudentName);

	istringstream studentAttributes(newStudentName);
	studentAttributes >> newStudentFirstName >> newStudentLastName;

	Student *student = new Student(newStudentFirstName, newStudentLastName);
	studentList.push_back(student);

	save(newStudentName, 0, studentSave);

	cout << "Student '" << newStudentFirstName << " " << newStudentLastName << "' added to course " << courseName << endl;

	cout << endl;
}

void Course::addStudent(string first, string last, string full) {
	Student *student = new Student(first, last, full);
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

	save(newAssignmentName,points, assignmentSave);

	cout << "Assignment '" << newAssignmentName << "' worth " << points << " points has been added to course " << courseName << endl;
}

void Course::addAssignment(string name, double points) {
	Assignment *assignment = new Assignment(name, points);
	assignmentList.push_back(assignment);
}

void Course::gradeAssignment() {

	string whichAssignment;
	cout << "Which assignment would you like to grade?";

	getline(cin, whichAssignment);

	string oneOrAll;
	cout << "Would you like to grade an assignment for a single student or all students?" << endl;
	cout << "1. Single student" << endl;
	cout << "2. All students" << endl;

	getline(cin, oneOrAll);

	if (oneOrAll == "1") {
		

		for (unsigned int i = 0; i < studentList.size(); i++) {
			if studentList[i]->
		}
	}

	if (oneOrAll == "2") {
		cout << "Enter the grade for each student:" << endl;
		cout << "(If you wish to exit grading process grading at any point, just enter 'c')" << endl;

		string grade;
		cout << studentList[i]->getFirstName << studentList[i]->getLastName << ": " << endl;
		getline(cin, grade);

		if (grade == "c") {
			return;
		}

		else {
			studentList[i]->
		}
	}

	cout << "Which assignment would you like to grade?";
}

void Course::save(string newItem, double numPoints, saveType addItem) {

	string line;
	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	vector<string> fileContent;
	string reset = newItem;

	while (getline(file, line)) {
		fileContent.push_back(line);
	}	

	for (unsigned int i = 0; i < fileContent.size(); i++) {

		vector<string>::iterator it = fileContent.begin() + i;
		newItem = reset;

		if (addItem == courseSave) {
			fileContent.insert(it, newItem.insert(0, tag(addItem)));
			break;
		}

		if (addItem == studentSave) {
			if (it->substr(1, it->back()) == courseName) {
				fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
				break;
			}
		}

		if (addItem == assignmentSave) {
			if (it->substr(1, it->back()) == courseName) {
				
				fileContent.insert(it + 1, newItem.insert(0, tag(addItem)).append(to_string(numPoints)));
			}
			if (it->substr(0, courseName.size()) == courseName && it->at(courseName.size()) == '$') {							
				fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
			}	
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

//adds all of the assignments in a course to each student
void Course::refresh() {
	studentList.front()->addStudentAssignment(assignmentList.front());
}

void Course::print() {

	cout << courseName << endl;

	cout << "Students:" << endl;
	for (unsigned int i = 0; i < studentList.size(); i++) {
		if (studentList[i] == studentList.back()) {
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << endl;

		}
		else {
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << ", ";
		}
	}	

	cout << "Assignments:" << endl;
	for (unsigned int i = 0; i < assignmentList.size(); i++) {
		if (assignmentList[i] == assignmentList.back()) {
			cout << assignmentList[i]->getAssignmentName() << assignmentList[i]->getPossiblePoints() << endl;
		}
		else {
			cout << assignmentList[i]->getAssignmentName() << assignmentList[i]->getPossiblePoints() << ", ";
		}
	}

	cout << endl;
}

void Course::courseMenu() {

	string menuChoice;

	cout << "What would you like to do in " << courseName << "?" << endl;
	cout << "1. Grade Assignment" << endl;
	cout << "2. New assignment" << endl;
	cout << "3. Add student(s)" << endl;
	cout << "4. Print course" << endl;

	getline(cin, menuChoice);

	if (menuChoice == "1") {
		gradeAssignment();
	}

	if (menuChoice == "2") {
		addAssignment();
	}

	if (menuChoice == "3") {
		addStudent();
	}

	if (menuChoice == "4") {
		print();
	}
}