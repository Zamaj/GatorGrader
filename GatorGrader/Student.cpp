#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Student.h"
#include "Assignment.h"
#include "Course.h"
#include "Instructor.h"

Student::Student() {

}

Student::Student(string first, string last, string full) {
	firstName = first;
	lastName = last;
	fullName = full;
}

std::string Student::getFirstName() {
	return firstName;
}

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

void Student::addStudentAssignment(Assignment *assignment) {
	assignments.push_back(assignment);
}

string Student::getFullName() {
	return fullName;
}

void Student::gradeStudentAssignment(string whichAssignment, Course * course) {
	
	for (unsigned int i = 0; i < assignments.size(); i++) 
	{
		if (assignments[i]->getAssignmentName() == whichAssignment) 
		{
			string pointsStr;
			double points;

			cout << "Enter grade:" << endl;

			getline(cin, pointsStr);

			points = atof(pointsStr.c_str());

			assignments[i]->setEarnedPoints(points);

			course->save(fullName, whichAssignment, points, Course::gradeSave);

			cout << fullName << ": " << points << "/" << assignments[i]->getPossiblePoints() << " on " << assignments[i]->getAssignmentName() << endl;
			return;
		}
	}

	cout << "No assignment '" << whichAssignment << "'" << endl;
}

void Student::gradeStudentAssignment(string assignment, double points, Course* course) {

	for (unsigned int i = 0; i < assignments.size(); i++) {
		if (assignments[i]->getAssignmentName() == assignment) {

			assignments[i]->setEarnedPoints(points);
			course->save(fullName, assignment, points, Course::gradeSave);
			
			cout << fullName << ": " << assignments[i]->getEarnedPoints() << "/" << assignments[i]->getPossiblePoints() << endl;
		}
	}
}

double Student::getAverageGrade() {
	double decGrade = 0.0;
	double earnedSum = 0;
	double possibleSum = 0;

	//for loop to get sum of the points student has earned and sum of the possible points
	//that can be earned
	for (int i = 0; i < assignments.size(); i++) {
		earnedSum = earnedSum + assignments[i]->getEarnedPoints();
		possibleSum = possibleSum + assignments[i]->getPossiblePoints();
	}

	//overall grade calculated by dividing sum of the earned points by sum of possible points
	decGrade = earnedSum / possibleSum;
	//calculateLetterGrade(decGrade);
	return decGrade;
}