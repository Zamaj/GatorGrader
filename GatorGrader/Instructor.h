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
class Student;

class Instructor {
private:
	std::string instructorName;
	std::vector<Course*> courseList;	
public:
	Course *currentCourse;
	Student *currentStudent;
	Instructor();
	Instructor(std::string name);	
	void setName(std::string name);
	std::string getName();
	int courseNum; 
	bool ifStudent;
	
	void firstTimeInstructor();
	void addCourse();
	void addCourse(std::string name);
	void removeCourse();
	void mainMenu();
	bool init();
	void findExistingStudent();
};