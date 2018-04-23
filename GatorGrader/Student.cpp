#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Student.h"
#include "Assignment.h"
#include "Course.h"
#include "Instructor.h"

/*The student class holds the data for each of the students in a course. Each student has a name
and constains a list of assignments. When a new assignment is added, each student in the course gets
a copy of the assignment. Because it contains graded assignments, the student class has methods that allow
those assignments to be graded. Additionally, a user can get the acerage grade for all of a student's assignments*/

Student::Student() 
{
	firstName = "Unknown";
	lastName = "Unkown";
	fullName = "Unkown";
}

Student::Student(string first, string last, string full) 
{
	firstName = first;
	lastName = last;
	fullName = full;
}

std::string Student::getFirstName()
{
	return firstName;
}

std::string Student::getLastName() 
{
	return lastName;
}

const vector<Assignment*>& Student::getStudentAssignments()
{
	return assignments;
}

// Adds assignment given input stats
void Student::addStudentAssignment(string name, double pointsEarned, double pointsPossible) 
{
	Assignment *assignment = new Assignment(name, pointsEarned, pointsPossible);
	assignments.push_back(assignment);	
}

// Adds assignment given assignment input
void Student::addStudentAssignment(Assignment *assignment) 
{
	assignments.push_back(assignment);
}

string Student::getFullName() 
{
	return fullName;
}


void Student::gradeStudentAssignment(string whichAssignment, Course * course) 
{
	
	// Finds assignment and set grade based on input
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

void Student::gradeStudentAssignment(string assignment, double points, Course* course) 
{
	//Grades automatically based on input stats
	for (unsigned int i = 0; i < assignments.size(); i++) 
	{
		if (assignments[i]->getAssignmentName() == assignment) 
		{

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