#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include "Assignment.h"
// #include "Student.h"
// #include "Course.h"
// #include "Instructor.h"
// #include <string>

Assignment::Assignment(std::string name, double points) {
	assignmentName = name;
	possiblePoints = points;
	earnedPoints = 0;
	assignmentGraded = false;
}

Assignment::Assignment(string name, double pointsEarned, double pointsPossible)
{
	assignmentName = name;
	possiblePoints = pointsPossible;
	earnedPoints = pointsEarned;
	assignmentGraded = true;
}

std::string Assignment::getAssignmentName() {
	return assignmentName;
}

void Assignment::setAssignmentName(std::string name) {
	assignmentName = name;
}

void Assignment::setPossiblePoints(double points) {
	possiblePoints = points;
}

double Assignment::getPossiblePoints() {
	return possiblePoints;
}

void Assignment::setEarnedPoints(double points) {
	earnedPoints = points;
	assignmentGraded = true;
}

double Assignment::getEarnedPoints() {
	if (assignmentGraded == true) {
		return earnedPoints;
	}
	else {
		cout << "Assignment not yet graded;" << endl;
		return earnedPoints;
	}
}

double Assignment::getPercentage() {
	return earnedPoints/possiblePoints;
}

bool Assignment::isGraded() {
	return assignmentGraded;
}

