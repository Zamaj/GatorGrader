#include <string>
#include <vector>
#include <fstream>
#include "Student.h"
#include "Course.h"
#include "Instructor.h"

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

Assignment::Assignment(string name, double points) {
	assignmentName = name;
	assignmentPoints = points;
}

string Assignment::getAssignmentName() {
	return assignmentName;
}