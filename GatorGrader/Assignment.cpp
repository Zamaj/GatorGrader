#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include "Assignment.h"
//#include "Student.h"
//#include "Course.h"
//#include "Instructor.h"

Assignment::Assignment(string name, double points) {
	assignmentName = name;
	assignmentPoints = points;
}

string Assignment::getAssignmentName() {
	return assignmentName;
}