#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include "Assignment.h"
// #include "Student.h"
// #include "Course.h"
// #include "Instructor.h"
// #include <string>

/*The assignment class is very basic. It stores an earned points and possible points 
variable which are used by the other classes. Each student has a list of assignments 
with grades and each course has a list of assignments that are ungraded. As it is only
used to store data, this class contains only getter/setter methods and constructors.*/

Assignment::Assignment(std::string name, double points) 
{
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

std::string Assignment::getAssignmentName() 
{
	return assignmentName;
}

void Assignment::setAssignmentName(std::string name) 
{
	assignmentName = name;
}

void Assignment::setPossiblePoints(double points) 
{
	possiblePoints = points;
}

double Assignment::getPossiblePoints() 
{
	return possiblePoints;
}

void Assignment::setEarnedPoints(double points)
{
	earnedPoints = points;
	assignmentGraded = true;
}

double Assignment::getEarnedPoints() 
{
	return earnedPoints;
}

double Assignment::getPercentage() 
{
	return earnedPoints/possiblePoints;
}

bool Assignment::isGraded() 
{
	return assignmentGraded;
}