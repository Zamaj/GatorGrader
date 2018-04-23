#pragma once
//#include "Assignment.h"
//#include "Student.h"
//#include "Course.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class Course;

class Instructor {
private:
	std::string instructorName;
	std::vector<Course*> courseList;
public:
	Course *currentCourse;
	Instructor();
	Instructor(std::string name);	
	void setName(std::string name);
	std::string getName();
	int courseNum; 
	bool ifStudent;
	//std::vector<Course*> &getCourseList();

	double gradeA;
	double gradeAMinus;
	double gradeBPlus;
	double gradeB;
	double gradeBMinus;
	double gradeCPlus;
	double gradeC;
	double gradeCMinus;
	double gradeDPlus;
	double gradeD;
	double gradeDMinus;
	
	void firstTimeInstructor();
	void addCourse();
	void addCourse(std::string name);
	void removeCourse();
	void listCourses();
	void mainMenu();
	bool init();
	void findExistingStudent();
	void setGradingScale();
};