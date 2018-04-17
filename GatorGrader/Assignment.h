#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Assignment {

private:
	std::string assignmentName;
	double possiblePoints;
	double earnedPoints;
	bool assignmentGraded;
public:
	Assignment(std::string name, double points);
	void setAssignmentName(std::string name);
	std::string getAssignmentName();
	void setPossiblePoints(double points);
	double getPossiblePoints();
	void setEarnedPoints(double points);
	double getEarnedPoints();
	double getPercentage();
	bool isGraded();
};