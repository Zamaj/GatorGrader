// #include "stdafx.h"
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
}

double Assignment::getEarnedPoints() {
	return earnedPoints;
}

double Assignment::getPercentage() {
	return earnedPoints/possiblePoints;
}

