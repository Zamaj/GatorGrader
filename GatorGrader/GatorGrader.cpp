#include "stdafx.h"
#include "GatorGrader.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Assignment::Assignment(string name, double points) {
	assignmentName = name;
	pointsPossible = points;
}

void Assignment::setAssignmentName(std::string name) {
	assignmentName = name;
}
string Assignment::getAssignmentName() {
	return assignmentName;
}
void Assignment::setPointsPossible(double points) {
	pointsPossible = points;
}
double Assignment::getPointsPossible() {
	return pointsPossible;
}
void Assignment::setPointsEarned(double points) {
	pointsEarned = points;
}
double Assignment::getPointsEarned() {
	return pointsEarned;
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

Instructor::Instructor() {

}

Instructor::Instructor(string name) {
	this->name = name;
}

void Instructor::setName(string name) {
	this->name = name;
}

string Instructor::getName() {
	return name;
}

void Instructor::addCourse() {
	string courseName;
	cout << "Please enter the name of a course: " << endl;
	cin >> courseName;
	Course* course = new Course(courseName);

	courseList.push_back(course);
}

void Instructor::firstTimeInstructor() {		
	cout << "Welcome to GatorGrader. Please enter your name:" << endl;
	cin >> name;

	addCourse();
}

void Instructor::menu() {
	string courseChoice;
	cout << "Enter a course name to view options for that course" << endl;
	cin >> courseChoice;

	for (unsigned int i = 0; i < courseList.size(); i++) {
		if (courseList[i]->getCourseName() == courseChoice) {
			currentCourse = courseList[i];
		}
		else {
			cout << "You do not have a course '" << courseChoice << "'" << endl;
			cout << "Please enter a valid course name:" << endl;			
		}
	}
}

int main()
{	
	Instructor *instructor = new Instructor();

	ifstream file("courses.txt"); /* Planning on having data for courses stored in 
	a text file, if it can't find the file then it assumes new user*/

	if (!file) {
		instructor->firstTimeInstructor();
	}
	else {
		string foundCourseName;
		getline(file, foundCourseName); /*Basically what I had planned on happening 
										here is parsing the text file to find the names
										of the courses and the students in each course.
										"courseList" is then populated with courses containing 
										vector "students" with the names of the students from that
										course (found in the file).
										*/
	}

	cout << "Your courses:" << endl;

	//for (unsigned int i = 0; i < instructor->courseList.size(); i++) { // Prints course names
	//	cout << instructor->courseList[i]->getCourseName() << endl;
	//}	

	instructor->menu();

    return 0;
}