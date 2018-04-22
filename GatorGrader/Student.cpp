#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Student.h"
#include "Assignment.h"
#include "Course.h"
#include "Instructor.h"

//constructor
Student::Student() {
}

//constructor
Student::Student(string first, string last, string full) {
	firstName = first;
	lastName = last;
	fullName = full;
}

//accessor method to get value of first name
std::string Student::getFirstName() {
	return firstName;
}

//accessor method to get value of last name
std::string Student::getLastName() {
	return lastName;
}

const vector<Assignment*>& Student::getStudentAssignments()
{
	return assignments;
}

void Student::addStudentAssignment(string name, double pointsEarned, double pointsPossible) {
	Assignment *assignment = new Assignment(name, pointsEarned, pointsPossible);
	assignments.push_back(assignment);	
}

//method to add assignment
void Student::addStudentAssignment(Assignment *assignment) {
	assignments.push_back(assignment);
}

//accessor method to get full name
string Student::getFullName() {
	return fullName;
}

//method to calculate overall grade in class
double Student::getAverageGrade() {

	double earnedSum = 0;
	double possibleSum = 0;

	//for loop to get sum of the points student has earned and sum of the possible points
	//that can be earned
	for (int i = 0; i < assignments.size(); i++) {
		earnedSum = earnedSum + assignments[i]->getEarnedPoints();
		possibleSum = possibleSum + assignments[i]->getPossiblePoints();
	}

	//overall grade calculated by dividing sum of the earned points by sum of possible points
	return earnedSum/possibleSum;
}

//method to grade assignment for student
void Student::gradeStudentAssignment(string whichAssignment, Course * course) {
	
	for (unsigned int i = 0; i < assignments.size(); i++) {
		if (assignments[i]->getAssignmentName() == whichAssignment) {
			string pointsStr;
			double points;

			//instructor inputs grade for assignment
			cout << "Enter grade:" << endl;
			getline(cin, pointsStr);
			points = atof(pointsStr.c_str());

			assignments[i]->setEarnedPoints(points);
			course->save(fullName, whichAssignment, 0, Course::gradeSave);

			cout << fullName << ": " << points << "/" << assignments[i]->getPossiblePoints() << " on " << assignments[i]->getAssignmentName() << endl;
			return;
		}
	}

	//checks if assignment exists
	cout << "No assignment '" << whichAssignment << "'" << endl;
}

//overloaded method to grade assignment
void Student::gradeStudentAssignment(string assignment, double points, Course* course) {

	for (unsigned int i = 0; i < assignments.size(); i++) {
		if (assignments[i]->getAssignmentName() == assignment) {

			assignments[i]->setEarnedPoints(points);
			course->save(fullName, assignment, points, Course::gradeSave);
			
			cout << fullName << ": " << assignments[i]->getEarnedPoints() << "/" << assignments[i]->getPossiblePoints() << endl;
		}
	}
}