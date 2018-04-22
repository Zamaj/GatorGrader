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

//constructor
Instructor::Instructor() {
	instructorName = "Unknown Instructor";
	courseNum = 0;
	ifStudent = false;
	//Instructor *instructor = new Instructor();
}

//constructor
Instructor::Instructor(string name) {
	this->instructorName = name;
}

//mutator method to set name of instructor
void Instructor::setName(string name) {
	this->instructorName = name;
}

//accessor method to get name of instructor
string Instructor::getName() {
	return instructorName;
}

//vector<Course*> &Instructor::getCourseList() {
//	return courseList;
//}

//method for when instructor is new, and has no courses 
void Instructor::firstTimeInstructor() {

	cout << "Welcome to GatorGrader. Please enter your name:" << endl;
	getline(cin, instructorName);

	addCourse();
}

//method to add a course
void Instructor::addCourse() {

	string newCourseName;
	cout << "Enter the name of a course: " << endl;
	getline(cin, newCourseName);

	vector<Course*>::iterator it;

	//checks to see if course already exists
	for (it = courseList.begin(); it != courseList.end(); it++) {
		string temp = (*it)->getCourseName();

		if (temp == newCourseName) {
			cout << "You already have a course named '" << newCourseName << "'." << endl;
			return;
		}
	}

	Course *course = new Course(newCourseName);
	//adds course to vector courseList
	courseList.push_back(course);
	course->save(newCourseName, 0, Course::courseSave);

	cout << "Course '" << newCourseName << "' added" << endl;
}

//overloaded method to add a course
void Instructor::addCourse(string name) {

	Course *course = new Course(name);
	courseList.push_back(course);
	currentCourse = course;
}

//method to remove a course
void Instructor::removeCourse() {

	string removeName;
	cout << "Enter the name of the course you would like to delete:" << endl;
	getline(cin, removeName);

	string confirmChoice;


	cout << "Are you sure you would like to delete '" << removeName << "' and all of its data?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	getline(cin, confirmChoice);

	//returns if user does not want to delete course
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

//main menu for instructor
void Instructor::mainMenu() {

	//lists the courses the instructor currently has
	cout << "Your Courses:" << endl;
	for (unsigned int i = 0; i < courseList.size(); i++) {
		cout << courseList[i]->getCourseName() << endl;
	}

	string courseChoice;

	while (true) {
		//instructor can add and remove courses or manage a course by typing in its name
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

			//checks if instructor has the entered course
			if (courseFound == false) {
				cout << "You have no course '" << courseChoice << "'." << endl;
			}
		}		
	}
}

//method that distinguishes between students and instructors
bool Instructor::init() {
	
	ifstream file("courses.txt");
	string courseName;
	string roleOption;

	//user chooses if they are a student or instructor
	cout << "Welcome to Gator Grader. Please enter if you are a student or instructor" << endl;
	getline(cin, roleOption);
	cout << endl;

	//if file doesnt exist, then instructor is new and doesnt have any courses
	if (!file) {
		firstTimeInstructor();
	}

	//if user is a student, calls method findExistingStudent()
	else if (roleOption == "student") {
		findExistingStudent();
		//sets bool variable ifStudent to true, which will be returned
		ifStudent = true;
	}

	//if user is an instructor
	else if (roleOption== "instructor") {
		string foundCourseData;
		string foundCourseName;
		
		//reads file line by line, storing each line in string variable foundCourseData
		while (getline(file, foundCourseData)) {

			//finds courses
			if (foundCourseData.front() == '#') {
				foundCourseData.erase(foundCourseData.begin());
				addCourse(foundCourseData);
				foundCourseName = foundCourseData;
				continue;
			}			

			//finds students
			if (foundCourseData.at(foundCourseName.size()) == '$') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundFirstName, foundLastName;
				istringstream studentName(foundCourseData);
				studentName >> foundFirstName >> foundLastName;
				currentCourse->addStudent(foundFirstName, foundLastName, foundCourseData);
				continue;
			}

			//finds assignments
			if (foundCourseData.at(foundCourseName.size()) == '&') {
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundAssignmentName;
				double foundAssignmentPoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundAssignmentName >> foundAssignmentPoints;
				currentCourse->addAssignment(foundAssignmentName, foundAssignmentPoints);
				continue;
			}
			//calls method mainMenu(), since user is an instructor
			mainMenu();
			
		}
		
	}

	return ifStudent;
	
}

//method to find student, when student enters their name. Then finds all of the courses that 
//specific student is in and prints them out
void Instructor::findExistingStudent() {
	
	vector <string> studentCourseList;
	string courseName;
	string line;
	//name you are looking for
	string studentName; 
	//student that already exists
	string existStudentName; 

	cout << "Please enter your name:" << endl;
	getline(cin, studentName);

	ifstream file("courses.txt");
	//goes to beginning of file
	file.seekg(0, ios::beg);

	//while loop to read file, line by line
	while (getline(file, line)) {

		//finds students, noted by $
		existStudentName = line.substr(line.find("$") + 1);

		//finds courses, denoted by #
		if (line.front() == '#') {
			//gets rid of #, so that line only contains the course name
			line.erase(line.begin());
			//courseName set to the course name
			courseName = line;
		}

		//checks if found student in file matches the student name entered
		if (studentName == existStudentName) {
		//adds course name to vector studentCourseList
			studentCourseList.push_back(courseName);
		}
	
	}

	cout << "Hello " << studentName << "!"<< endl;
	cout << "Your courses:" << endl;

	//while loop to print out vector studentCourseList
	while (!studentCourseList.empty()) {
		for (std::vector<string>::const_iterator i = studentCourseList.begin(); i != studentCourseList.end(); ++i)
			std::cout << *i << endl;
		studentCourseList.pop_back();
	}
	return; 

}