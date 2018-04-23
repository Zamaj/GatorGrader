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
public:
	std::vector<Course*> courseList;
	Course *currentCourse;
	Instructor();
	Instructor(std::string name);	
	void setName(std::string name);
	std::string getName();
	//void setCredits(int credits);
	//int getCredits();
	int courseNum; 
	int numOfCredits;
	//std::vector<Course*> &getCourseList();
	void firstTimeInstructor();
	void addCourse();
	void addCourse(std::string name, int credits);
	void removeCourse();
	void mainMenu();
	void init();
	void findExistingStudent();
};