#include "stdafx.h"
#include "GatorGrader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

Assignment::Assignment(string name, double points) {
	assignmentName = name;
	assignmentPoints = points;
}

string Assignment::getAssignmentName() {
	return assignmentName;
}

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

Instructor::Instructor() {
	instructorName = "Unkown Instructor";
}

Instructor::Instructor(string name) {
	this->instructorName = name;
}

void Instructor::setName(string name) {
	this->instructorName = name;
}

string Instructor::getName() {
	return instructorName;
}

vector<Course*> &Instructor::getCourseList() { 
	return courseList;
}

void Instructor::firstTimeInstructor() {
	cout << "Welcome to GatorGrader. Please enter your name:" << endl;
	getline(cin, instructorName);

	addCourse();
}

void Instructor::addCourse() {
	string courseName;
	cout << "Enter the name of a course to begin: " << endl;
	getline(cin, courseName);
	Course* course = new Course(courseName);

	courseList.push_back(course);
}

void Instructor::addCourse(string name) {
	Course *course = new Course(name);
	courseList.push_back(course);	
	currentCourse = course;
}

void Instructor::mainMenu() {
	cout << "Your Courses:" << endl;
	for (unsigned int i = 0; i < courseList.size(); i++) {
		cout << courseList[i]->getCourseName() << endl;
	}

	string courseChoice;
	
	while(true) {
		cout << "Enter a course name to view options for that course or choose an option below:" << endl;
		cout << "1. Add course" << endl;
		cout << "2. Remove course" << endl;

		getline(cin, courseChoice);

		bool courseFound = false;

		if (courseChoice == "1" || courseChoice == "Add course" || courseChoice == "add course" || courseChoice == "Add Course") {
			addCourse();
		}

		if (courseChoice == "2" || courseChoice == "Remove course" || courseChoice == "remove course" || courseChoice == "Remove Course") {
			//removeCourse();
		}

		for (unsigned int i = 0; i < courseList.size(); i++) {
			if (courseList[i]->getCourseName() == courseChoice) {
				currentCourse = courseList[i];
				courseFound = true;
				currentCourse->courseMenu();
			}			
		}

		if (courseFound == false) {
			cout << "You have no course '" << courseChoice << "'." << endl;
		}
	}
}

void Instructor::init() {
	ifstream file("courses.txt");

	if (!file) {
		firstTimeInstructor();
	}
	else {
		string foundCourseData;
		while (getline(file, foundCourseData)) {

			if (foundCourseData.front() == '#') {
				foundCourseData.erase(foundCourseData.begin());
				addCourse(foundCourseData);
			}

			if (foundCourseData.front() == '$') {
				foundCourseData.erase(foundCourseData.begin());
				string foundFirstName, foundLastName;
				istringstream studentName(foundCourseData);
				studentName >> foundFirstName >> foundLastName;
				currentCourse->addStudent(foundFirstName, foundLastName);
			}

			if (foundCourseData.front() == '@') {
				foundCourseData.erase(foundCourseData.begin());
				string foundCourseName;
				double foundCoursePoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundCourseName >> foundCoursePoints;
				currentCourse->addAssignment(foundCourseName, foundCoursePoints);
			}
		}
	}
}

int main()
{	
	Instructor *instructor = new Instructor();
	
	instructor->init();

	instructor->mainMenu();

	//instructor->currentCourse->print();

    return 0;
}