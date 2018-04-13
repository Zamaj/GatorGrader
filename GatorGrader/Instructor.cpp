#include "stdafx.h"
#include "Instructor.h"
#include "Assignment.h"
#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

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

//vector<Course*> &Instructor::getCourseList() {
//	return courseList;
//}

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

void Instructor::removeCourse() {

}

void Instructor::mainMenu() {
	cout << "Your Courses:" << endl;
	for (unsigned int i = 0; i < courseList.size(); i++) {
		cout << courseList[i]->getCourseName() << endl;
	}

	string courseChoice;

	while (true) {
		cout << "Enter a course name to view options for that course or choose an option below:" << endl;
		cout << "1. Add course" << endl;
		cout << "2. Remove course" << endl;

		getline(cin, courseChoice);

		bool courseFound = false;

		if (courseChoice == "1" || courseChoice == "Add course") {
			addCourse();
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