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

//Instructor class contains higher-level functionality, such as managing courses

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
	course->save("", newCourseName, 0, Course::courseSave);

	cout << "Course '" << newCourseName << "' added" << endl;
}

void Instructor::addCourse(string name) {
	Course *course = new Course(name);
	courseList.push_back(course);
	currentCourse = course;
}

void Instructor::visualizeCourse() {

	// method to visualize course grades by creating a histogram
	// with the following predefinited categories (inclusive) based on percentage points
	// calculated with the same method of earned points divided by possible points:
	// A: 90+
	// B: 80-89
	// C: 70-79
	// D: 60-69
	// F: 0-59

	// stores the insructor's chosen course to visualize
	string courseGraphSelection;

	cout << "Enter the name of a course you would like to visualize grades for:" << endl;
	getline(cin, courseGraphSelection);

	bool courseGraphSelectionFound = false;

	// loops through course list to check for valid course input
	for (unsigned int i = 0; i < courseList.size(); i++)
	{
		if (courseList[i]->getCourseName() == courseGraphSelection)
		{
			currentCourse = courseList[i];
			courseGraphSelectionFound = true;
		}
	}

	if (courseGraphSelectionFound == false)
	{
		cout << "Course not found" << endl;
		return;
	}

	// initialize frequency counters
	int acount = 0;
	int bcount = 0;
	int ccount = 0;
	int dcount = 0;
	int fcount = 0;

	int gradeNumber;

	for (int i = 0; i < currentCourse->getStudentList().size(); i++) 
	{
		double studentAverageGrade = currentCourse->getStudentList()[i]->getAverageGrade();

		// sets switch input
		if (studentAverageGrade >= 0.9)
		{
			acount++;
		}

		if (studentAverageGrade >= 0.8 && studentAverageGrade < 0.9)
		{
			bcount++;
		}

		if (studentAverageGrade >= 0.7 && studentAverageGrade < 0.8)
		{
			ccount++;
		}

		if (studentAverageGrade >= 0.6 && studentAverageGrade < 0.7)
		{
			dcount++;
		}

		if (studentAverageGrade < 0.6)
		{
			fcount++;
		}
	}

	// creates historgram, category by category
	cout << "A: ";
	for (int ac = 0; ac<acount; ac++)
	{
		cout << "x";
	}
	cout << endl;

	cout << "B: ";
	for (int bc = 0; bc<bcount; bc++)
	{
		cout << "x";
	}
	cout << endl;

	cout << "C: ";
	for (int cc = 0; cc<ccount; cc++)
	{
		cout << "x";
	}
	cout << endl;

	cout << "D: ";
	for (int dc = 0; dc<dcount; dc++)
	{
		cout << "x";
	}
	cout << endl;

	cout << "F: ";
	for (int fc = 0; fc<fcount; fc++)
	{
		cout << "x";
	}

	cout << endl;
}

// Removes course from memory and file
void Instructor::removeCourse()
{
	string removeName;
	cout << "Enter the name of the course you would like to delete:" << endl;
	getline(cin, removeName);

	string confirmChoice;

	
	cout << "Are you sure you would like to delete '" << removeName << "' and all of its data?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	getline(cin, confirmChoice);

	if (confirmChoice != "1")
	{
		return;
	}		
	
	vector<Course*>::iterator it;
	for (it = courseList.begin(); it != courseList.end();) 
	{
		if ((*it)->getCourseName() == removeName) 
		{
			delete *it;
			it = courseList.erase(it);
		}
		else
		{
			it++;
		}
	}

	cout << "Course '" << removeName << "' has been removed" << endl;
}

void Instructor::mainMenu()
{

	cout << "Your Courses:" << endl;
	for (unsigned int i = 0; i < courseList.size(); i++)
	{
		cout << courseList[i]->getCourseName() << endl;
	}

	string courseChoice;

	while (true) {
		cout << "Enter a course name to view options for that course or choose an option below:" << endl;
		cout << "1. Add course" << endl;
		cout << "2. Visualize course grades" << endl;
		cout << "3. Remove course" << endl;
		cout << "4. Exit" << endl;

		getline(cin, courseChoice);

		bool courseFound = false;

		if (courseChoice == "1" || courseChoice == "Add course" || courseChoice == "add course" || courseChoice == "Add Course") {
			addCourse();
		}

		else if (courseChoice == "2") {
			visualizeCourse();
		}

		else if (courseChoice == "3") {
			removeCourse();
		}

		else if (courseChoice == "4")
		{
			exit(0);
		}

		else
		{
			for (unsigned int i = 0; i < courseList.size(); i++) 
			{
				if (courseList[i]->getCourseName() == courseChoice) 
				{
					currentCourse = courseList[i];
					courseFound = true;
					currentCourse->courseMenu();
				}
			}

			if (courseFound == false)
			{
				cout << "You have no course '" << courseChoice << "'." << endl;
			}
		}		
	}
}

// Runs ons startup to load data from file into memory
void Instructor::init() 
{
	string currentStudent;

	ifstream file("courses.txt");

	if (!file)
	{
		firstTimeInstructor();
	}
	else 
	{
		string foundCourseData;
		string foundCourseName;

		while (getline(file, foundCourseData))
		{

			//Different data types designated by symbols

			// Course
			if (foundCourseData.front() == '#') 
			{
				foundCourseData.erase(foundCourseData.begin());
				addCourse(foundCourseData);
				foundCourseName = foundCourseData;
				continue;
			}

			// Student
			if (foundCourseData.at(foundCourseName.size()) == '$') 
			{
				foundCourseData.erase(0, foundCourseName.size() + 1);
				currentStudent = foundCourseData;
				string foundFirstName, foundLastName;
				istringstream studentName(foundCourseData);
				studentName >> foundFirstName >> foundLastName;
				currentCourse->addStudent(foundFirstName, foundLastName, foundCourseData);
				continue;
			}

			// Student Assignment
			if (foundCourseData.at(foundCourseName.size()) == '@') {

				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundGradedAssignmentName;
				double foundGradedAssignmentPoints;
				double foundOriginalAssignmentPoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundGradedAssignmentName >> foundGradedAssignmentPoints;

				for (unsigned int i = 0; i < currentCourse->getAssignmentList().size(); i++) {

					if (currentCourse->getAssignmentList()[i]->getAssignmentName() == foundGradedAssignmentName) {
						foundOriginalAssignmentPoints = currentCourse->getAssignmentList()[i]->getPossiblePoints();
						break;
					}
				}
								
				for (unsigned int i = 0; i < currentCourse->getStudentList().size(); i++) {					

					if (currentCourse->getStudentList()[i]->getFullName() == currentStudent) {


						currentCourse->getStudentList()[i]->addStudentAssignment(foundGradedAssignmentName, foundGradedAssignmentPoints, foundOriginalAssignmentPoints);
					}
				}

				continue;
			}

			// Course assignment
			if (foundCourseData.at(foundCourseName.size()) == '&')
			{
				foundCourseData.erase(0, foundCourseName.size() + 1);
				string foundAssignmentName;
				double foundAssignmentPoints;
				istringstream assignmentAttributes(foundCourseData);
				assignmentAttributes >> foundAssignmentName >> foundAssignmentPoints;
				currentCourse->addAssignment(foundAssignmentName, foundAssignmentPoints);
				continue;
			}
		}		
	}
}