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
	instructorName = "Unknown Instructor";
	courseNum = 0;
	ifStudent = false;
	//Instructor *instructor = new Instructor();
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

	string newCourseName;
	cout << "Enter the name of a course: " << endl;
	getline(cin, newCourseName);

	vector<Course*>::iterator it;

	for (it = courseList.begin(); it != courseList.end(); it++) {
		string temp = (*it)->getCourseName();

		if (temp == newCourseName) {
			cout << "You already have a course named '" << newCourseName << "'." << endl;
			return;
		}
	}

	Course *course = new Course(newCourseName);
	courseList.push_back(course);
	course->save(newCourseName, 0, Course::courseSave);

	cout << "Course '" << newCourseName << "' added" << endl;
}

void Instructor::addCourse(string name) {
	Course *course = new Course(name);
	courseList.push_back(course);
	currentCourse = course;
}

void Instructor::removeCourse() {
	string removeName;
	cout << "Enter the name of the course you would like to delete:" << endl;
	getline(cin, removeName);

	string confirmChoice;

	
	cout << "Are you sure you would like to delete '" << removeName << "' and all of its data?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	getline(cin, confirmChoice);

	if (confirmChoice != "1") {
		return;
	}		
	
	vector<Course*>::iterator it;
	for (it = courseList.begin(); it != courseList.end();) {
		if ((*it)->getCourseName() == removeName) {
			delete *it;
			it = courseList.erase(it);
		}
		else {
			it++;
		}
	}

	cout << "Course '" << removeName << "' has been removed" << endl;
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

		if (courseChoice == "1" || courseChoice == "Add course" || courseChoice == "add course" || courseChoice == "Add Course") {
			addCourse();
		}

		else if (courseChoice == "2" || courseChoice == "Remove course" || courseChoice == "remove course" || courseChoice == "Remove Course") {
			removeCourse();
		}

		else {
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
}

bool Instructor::init() {
	//bool ifStudent = false;
	ifstream file("courses.txt");
	string courseName;
	string roleOption;
	cout << "Welcome to Gator Grader. Please enter if you are a student or instructor" << endl;
	getline(cin, roleOption);
	cout << endl;

	if (!file) {
		firstTimeInstructor();
		//return ifStudent;
	}
	else if (roleOption == "student") {
		findExistingStudent();
		ifStudent = true;
		//return ifStudent;
	}
	else if (roleOption== "instructor") {
		string foundCourseData;
		string foundCourseName;
		//findExistingStudent();
		while (getline(file, foundCourseData)) {

			if (foundCourseData.front() == '#') {
				foundCourseData.erase(foundCourseData.begin());
				addCourse(foundCourseData);
				foundCourseName = foundCourseData;
				//courseName = foundCourseName;
				//findExistingStudent(courseName);
				continue;
			}			

			if (foundCourseData.at(foundCourseName.size()) == '$') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundFirstName, foundLastName;
				istringstream studentName(foundCourseData);
				studentName >> foundFirstName >> foundLastName;
				currentCourse->addStudent(foundFirstName, foundLastName, foundCourseData);
				continue;
			}

			if (foundCourseData.at(foundCourseName.size()) == '&') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundAssignmentName;
				double foundAssignmentPoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundAssignmentName >> foundAssignmentPoints;
				currentCourse->addAssignment(foundAssignmentName, foundAssignmentPoints);
				continue;
			}
			mainMenu();
			//return ifStudent;
		}
		//return false;
	}
	return ifStudent;
	//findExistingStudent(courseName);
	//return ifStudent;
}
void Instructor::findExistingStudent() {
	//std::vector<Course*> studentCourseList;
	//Instructor *studentCourse = new Instructor(courseName);
	vector <string> studentCourseList;
	string courseName;
	//char courseList[20];
	string line;
	string studentName; //name you are looking for
	string existStudentName; //student that already exists
	cout << "Please enter your name:" << endl;
	getline(cin, studentName);
	ifstream file("courses.txt");
	//existStudentName = line.substr(line.find("$") + 1);
	file.seekg(0, ios::beg);
	while (getline(file, line)) {
		existStudentName = line.substr(line.find("$") + 1);
		if (line.front() == '#') {
			line.erase(line.begin());
			courseName = line;
		}
		if (studentName == existStudentName) {
			//courseList[courseNum] = courseName;
			studentCourseList.push_back(courseName);
			//studentCourse->save(courseName);
		}
	

	}
	cout << "Hello " << studentName << "!"<< endl;
	cout << "Your courses:" << endl;
	while (!studentCourseList.empty()) {
		//cout << studentCourseList << endl;
		for (std::vector<string>::const_iterator i = studentCourseList.begin(); i != studentCourseList.end(); ++i)
			std::cout << *i << endl;
		studentCourseList.pop_back();
	}
	return; 

}