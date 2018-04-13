#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Assignment {

private:
	std::string assignmentName;
	double assignmentPoints;
public:
	Assignment(std::string name, double points);
	void setAssignmentName();
	std::string getAssignmentName();
	void setPoints();
	double getPoints();
};