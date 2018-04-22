#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include "Assignment.h"
// #include "Student.h"
// #include "Course.h"
// #include "Instructor.h"
// #include <string>

//constructor
Assignment::Assignment(std::string name, double points) {
	assignmentName = name;
	possiblePoints = points;
	earnedPoints = 0;
	assignmentGraded = false;
}

//accessor method to get name of assignment
std::string Assignment::getAssignmentName() {
	return assignmentName;
}

//mutator method to set value of assignment name
void Assignment::setAssignmentName(std::string name) {
	assignmentName = name;
}

//mutator method to set value of the possible points
void Assignment::setPossiblePoints(double points) {
	possiblePoints = points;
}

//accessor method to get value of possible points
double Assignment::getPossiblePoints() {
	return possiblePoints;
}

//mutator method to set value of earned points
void Assignment::setEarnedPoints(double points) {
	earnedPoints = points;
//assignment is graded, bool value set to true
	assignmentGraded = true;
}

//accessor method to get value of earned points
double Assignment::getEarnedPoints() {
	if (assignmentGraded == true) {
		return earnedPoints;
	}
	else {
		cout << "Assignment not yet graded;" << endl;
		return earnedPoints;
	}
}

//accessor method to get grade percentage
double Assignment::getPercentage() {
	return earnedPoints/possiblePoints;
}

